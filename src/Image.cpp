#include "Image.hpp"
#include "StringOperations.hpp"

#include <algorithm>
#include <cctype>
#include <string>

Image::Image(){
    renderImage = PrepareNewRender(vec::IVec2(0,0));
}
Image::Image(vec::IVec2 vec){
    size = vec;
    renderImage = PrepareNewRender(size);
}
Image::~Image(){
    DeallocateRender();
    DeleteAllLayers();
}

int Image::GetLayersNumber(){
    int layerNum = 0;
    Layer* curLayer = firstLayer;
    while(curLayer!=nullptr){
        layerNum+=1;
        curLayer = curLayer->nextLayer;
    }
    return layerNum;
}
vec::IVec2 Image::GetLayerPosition(int layerId){
    if(layerId<GetLayersNumber()){
        Layer* curLayer = firstLayer;
        for(int i=0; i<layerId; i++){
            curLayer = curLayer->nextLayer;
        }
        return curLayer->GetStart();
    }
    return vec::IVec2::Undefined;
}
vec::IVec2 Image::GetLayerSize(int layerId){
    if(layerId<GetLayersNumber()){
        Layer* curLayer = firstLayer;
        for(int i=0; i<layerId; i++){
            curLayer = curLayer->nextLayer;
        }
        return curLayer->GetSize();
    }
    return vec::IVec2::Undefined;
}

void Image::AddLayerStart(){
    Layer* newLayer = new Layer();
    if(firstLayer == nullptr){
        firstLayer = newLayer;
        lastLayer = newLayer;

        focusedLayerId = newLayer->GetLayerId();
        return;
    }
    firstLayer->previousLayer = newLayer;
    newLayer->nextLayer = firstLayer;
    firstLayer = newLayer;

    focusedLayerId = newLayer->GetLayerId();
}
void Image::AddLayerEnd(){
    if(GetLayersNumber() == 0){
        AddLayerStart();
        UpdateLastLayer();
        return;
    }
    Layer* newLayer = new Layer();
    newLayer->previousLayer = lastLayer;
    lastLayer->nextLayer = newLayer;
    lastLayer = newLayer;
    focusedLayerId = newLayer->GetLayerId();
}
void Image::AddLayer(int newLayerId){
    if(newLayerId == 0){
        AddLayerStart();
    }
    else if(newLayerId>GetLayersNumber()){
        return;
    }
    else if(newLayerId==GetLayersNumber()){
        AddLayerEnd();
    }
    else{
        Layer newLayer = Layer();
        Layer* curLayer = firstLayer;
        for(int i=0; i<newLayerId; i++){
            curLayer = curLayer->nextLayer;
        }
        newLayer.previousLayer = curLayer;
        newLayer.nextLayer = curLayer->nextLayer;
        curLayer->nextLayer->previousLayer = &newLayer;
        curLayer->nextLayer = &newLayer;

        focusedLayerId = newLayer.GetLayerId();
    }
}

Layer* Image::GetLayer(int layerId){
    Layer* curLayer = firstLayer;
    if(layerId>=GetLayersNumber()){
        return nullptr;
    }
    for(int i=0; i<layerId; i++){
        curLayer = curLayer->nextLayer;
    }
    return curLayer;
}
Layer* Image::GetFirstLayer(){
    return firstLayer;
}
Layer* Image::GetLastLayer(){
    return lastLayer;
}

void Image::MoveLayer(int layerId, int newLayerId){
    if((GetLayer(layerId)==nullptr && GetLayer(newLayerId)==nullptr) || layerId == newLayerId){
        return;
    }
    Layer* layer = GetLayer(layerId);
    Layer* layerOnPosition = GetLayer(newLayerId);
    if(layer->previousLayer==nullptr){
        layer->nextLayer->previousLayer = nullptr;
    }
    if(layer->nextLayer==nullptr){
        layer->previousLayer->nextLayer = nullptr;
    }
    layer->previousLayer = layerOnPosition->previousLayer;
    layer->nextLayer = layerOnPosition;
    if(layer->previousLayer == nullptr){
        firstLayer = layer;
    }
    if(layer->nextLayer == nullptr){
        lastLayer = layer;
    }

    focusedLayerId = layer->GetLayerId();
}

void Image::SwapLayers(int layer1Id, int layer2Id){
    if(GetLayer(layer1Id)==nullptr || GetLayer(layer2Id)==nullptr){
        return;
    }
    Layer* layer1 = GetLayer(layer1Id);
    Layer* layer2 = GetLayer(layer2Id);
    Layer* layer1last = layer1->previousLayer;//null
    Layer* layer1next = layer1->nextLayer;//layer2
    Layer* layer2last = layer2->previousLayer;//layer1
    Layer* layer2next = layer2->nextLayer;//null

    if(layer1last == nullptr){
        firstLayer = layer2;
        layer2->previousLayer = nullptr;
    }
    else{
        if(layer1last == layer2){
            layer2->previousLayer = layer1;
        }
        else{
            layer2->previousLayer = layer1last;
        }
    }
    if(layer1next == nullptr){
        lastLayer = layer2;
        layer2->nextLayer = nullptr;
    }
    else{
        if(layer1next == layer2){
            layer2->nextLayer = layer1;
        }
        else{
            layer2->nextLayer = layer1next;
        }
    }
    if(layer2last == nullptr){
        firstLayer = layer1;
        layer1->previousLayer = nullptr;
    }
    else{
        if(layer2last == layer1){
            layer1->previousLayer = layer2;
        }
        else{
            layer1->previousLayer = layer2last;
        }
    }
    if(layer2next == nullptr){
        lastLayer = layer1;
        layer1->nextLayer = nullptr;
    }
    else{
        if(layer2next == layer1){
            layer1->nextLayer = layer2;
        }
        else{
            layer1->nextLayer = layer2next;
        }
    }

    focusedLayerId = layer1->GetLayerId();


}

void Image::DeleteAllLayers(){
    Layer* curLayer = firstLayer;
    while(curLayer!= nullptr){
        Layer* nextLayer = curLayer->nextLayer;
        delete curLayer;
        curLayer = nextLayer;
    }
    firstLayer = nullptr;
    lastLayer = nullptr;

}

void Image::UpdateLastLayer(){
    if(firstLayer==nullptr){
        return;
    }
    Layer* curLayer = firstLayer;
    while(curLayer->nextLayer!=nullptr){
        curLayer = curLayer->nextLayer;
    }
    lastLayer = curLayer;
}

void Image::UpdateRender(){
    ClearRender();
    Layer* curLayer = lastLayer;
    while(curLayer!=nullptr){
        if(curLayer->GetSize()!=vec::IVec2::Undefined && curLayer->GetSize()!=vec::IVec2(0,0)){
            for(int i=0; i<curLayer->GetSize().x; i++){
                for(int j=0; j<curLayer->GetSize().y; j++){
                    if(curLayer->GetStart().x+i>=size.x || curLayer->GetStart().y+j>=size.y || curLayer->GetStart().x+i<0 || curLayer->GetStart().y+j<0){
                        continue;
                    }
                    Pixel* renderPixel = this->renderImage[i+curLayer->GetStart().x][j+curLayer->GetStart().y];
                    if(curLayer->hasBuffer()){
                        if(curLayer->GetBuffer(vec::IVec2(i,j)) != nullptr && (renderPixel==nullptr)){
                            this->renderImage[i+curLayer->GetStart().x][j+curLayer->GetStart().y] = curLayer->GetBuffer(vec::IVec2(i,j));
                        }
                    }
                    else{
                        if(curLayer->GetPixel(vec::IVec2(i,j)) != nullptr && (renderPixel==nullptr)){
                            this->renderImage[i+curLayer->GetStart().x][j+curLayer->GetStart().y] = curLayer->GetPixel(vec::IVec2(i,j));
                        }
                    }
                }
            }
        }
        curLayer = curLayer->previousLayer;
    }
}

void Image::Resize(vec::IVec2 vec){
    Pixel*** newArr = PrepareNewRender(vec);
    for(int i = 0; i< std::min(vec.x, size.x); i++){
        for(int j=0; j<std::min(vec.y, size.y); j++){
            newArr[i][j] = renderImage[i][j];
        }
    }

    DeallocateRender();

    renderImage = newArr;

    size = vec::IVec2(vec);
}

vec::IVec2 Image::GetSize(){
    return size;
}

Pixel*** Image::GetRender(){
    return renderImage;
}

void Image::Open(std::string path){
    AddLayerEnd();
    lastLayer->Open(path);
}
void Image::Save(std::string path){
    UpdateRender();
    if(size!=vec::IVec2(0,0) && renderImage!=nullptr){
        std::ofstream file(path);
        file<<"P3\n# created in gimpRipoff made by Bejmach\n"<<size.x<<" "<<size.y<<"\n255\n";
        for(int y=0; y<size.y; y++){
            for(int x=0; x<size.x; x++){
                if(renderImage[x][y]==nullptr){
                    file<<255<<"\n"<<255<<"\n"<<255<<"\n";
                }
                else{
                    file<<static_cast<int>(renderImage[x][y]->color.R)<<"\n"<<static_cast<int>(renderImage[x][y]->color.G)<<"\n"<<static_cast<int>(renderImage[x][y]->color.B)<<"\n";
                }
            }
        }
    }
}
void Image::Close(){
    DeleteAllLayers();
    UpdateRender();
}

Pixel*** Image::PrepareNewRender(vec::IVec2 vec){
    Pixel*** newArr = new Pixel**[vec.x];
    for(int i=0; i<vec.x; i++){
        newArr[i] = new Pixel*[vec.y];
        for(int j=0; j<vec.y; j++){
            newArr[i][j] = nullptr;
        }
    }
    return newArr;
}
void Image::DeallocateRender(){
    for(int i=0; i<size.x; i++){
        delete[] renderImage[i];
    }
    delete[] renderImage;
}
void Image::ClearRender(){
    for(int i=0; i<size.x; i++){
        for(int j=0; j<size.y; j++){
            renderImage[i][j]=nullptr;
        }
    }
}

void Image::ScaleToContent(){
    if(GetLayersNumber()==0){
        return;
    }
    Layer* curLayer = lastLayer;
    if(curLayer == nullptr) return;
    vec::IVec2 minPosition = curLayer->GetStart();
    vec::IVec2 maxPosition = curLayer->GetSize()+curLayer->GetStart();
    while(curLayer->previousLayer!=nullptr){
        curLayer = curLayer->previousLayer;
        if(curLayer->GetStart().x<minPosition.x){
            minPosition.x = curLayer->GetStart().x;
        }
        if(curLayer->GetStart().y<minPosition.y){
            minPosition.y = curLayer->GetStart().y;
        }
        if(curLayer->GetStart().x+curLayer->GetSize().x-1>maxPosition.x){
            maxPosition.x = curLayer->GetStart().x+curLayer->GetSize().x-1;
        }
        if(curLayer->GetStart().y+curLayer->GetSize().y-1>maxPosition.y){
            maxPosition.y = curLayer->GetStart().y+curLayer->GetSize().y-1;
        }
    }
    vec::IVec2 finalSize = maxPosition - minPosition;
    this->Resize(finalSize);
    curLayer = lastLayer;
    while(curLayer!=nullptr){
        curLayer->Move(curLayer->GetStart() + minPosition);
        curLayer = curLayer->previousLayer;
    }
}


std::pair<bool, std::string> Image::ConsoleInput(std::string command){
    //transform to lowercase
    std::transform(command.begin(), command.end(), command.begin(), [](unsigned char c){ return std::tolower(c); });
    std::vector<std::string> commandForm = SO::Split(command, " ");
    if(commandForm.size()==0){
        return {false, "empty command"};
    }
    else if(commandForm[0] == "layer"){
        if(commandForm.size()<2){
            return {false, "wrong command"};
        }
        if(commandForm[1] == "swap"){
            if(commandForm.size()<4){
                return {false, "need 2 layers to swap\ncorrect form \"layer swap {layerId1} {layerId2}\""};
            }
            else if(!(SO::isNumeric(commandForm[2]) && SO::isNumeric(commandForm[3]))){
                return {false, "layers provided needs to be numbers"};
            }
            else if(GetLayersNumber()-1<std::stoi(commandForm[2]) || GetLayersNumber()-1<std::stoi(commandForm[3])){
                return {false, "layer provided exceed the layer range"};
            }
            else{
                SwapLayers(std::stoi(commandForm[2]), std::stoi(commandForm[3]));
                return {true, "Layers correctly swapped"};
            }
        }
        if(commandForm[1] == "set"){
            if(commandForm.size()<3){
                return {false, "need layer number to set\ncorrect form \"layer set {layerId1}\""};
            }
            else if(!SO::isNumeric(commandForm[2])){
                return {false, "layer provided needs to be number"};
            }
            else if(GetLayersNumber()-1<std::stoi(commandForm[2])){
                return {false, "layer provided exceed the layer range"};
            }
            else{
                this->focusedLayerId = std::stoi(commandForm[2]);
                return {false, "layer focus changed to "+std::to_string(focusedLayerId)};
            }
        }

    }

    return {false, "no command found, try use \'help\' to check if command provided by you, really exist"};
}

void Image::ApplyLayerBuffer(){
    Layer* layer = GetLayer(focusedLayerId);
    if(layer!=nullptr && layer->buffer!=nullptr){
        layer->Dealocate();
        layer->layerMap = layer->buffer;
        layer->buffer = nullptr;
    }
}

void Image::RevertLayerBuffer(){
    Layer* layer = GetLayer(focusedLayerId);
    if(layer!=nullptr && layer->buffer!=nullptr){
        layer->DeallocateBuffer();
        layer->buffer = nullptr;
    }
}
