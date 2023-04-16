// Edgar Robitaille
// erobita1

template <typename DataType>
TDataLoop<DataType>::TDataLoop() : start(nullptr), count(0) {}

template <typename DataType>
TDataLoop<DataType>::TDataLoop(const DataType & data) {
    start = new _Node{data, nullptr, nullptr};
    start->next = start;
    start->prev = start;
    count = 1;
}

template <typename DataType>
TDataLoop<DataType>::TDataLoop(const TDataLoop<DataType> & rhs) { 

}

template <typename DataType>
TDataLoop<DataType> & TDataLoop<DataType>::operator=(const TDataLoop<DataType> & rhs) {

}

template <typename DataType>
TDataLoop<DataType>::~TDataLoop() {

}

template <typename DataType>
bool TDataLoop<DataType>::operator==(const TDataLoop<DataType> & rhs) const { 

}

template <typename DataType>
TDataLoop<DataType> & TDataLoop<DataType>::operator+=(const DataType & data) {

}

template <typename DataType>
TDataLoop<DataType> TDataLoop<DataType>::operator+(const TDataLoop<DataType> & rhs) const {

}

template <typename DataType>
TDataLoop<DataType> & TDataLoop<DataType>::operator^(int offset) {

}

template <typename DataType>
TDataLoop<DataType> & TDataLoop<DataType>::splice(TDataLoop<DataType> & rhs, size_t pos) {

}

template <typename DataType>
std::ostream & operator<<(std::ostream & os, const TDataLoop<DataType> & dl) {

}

