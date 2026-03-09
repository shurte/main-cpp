#pragma once

#include <memory>
#include <vector>

constexpr unsigned int defaultVertexSize = 4;
constexpr unsigned int numberOfCoordinates = 3;

class UiObject {
    public:
        UiObject()
            : vertexSize(defaultVertexSize)
            , data(new float[defaultVertexSize * numberOfCoordinates]) {
        }

        UiObject(unsigned int vertexSize)
            : vertexSize(vertexSize)
            , data(new float[vertexSize * numberOfCoordinates]) {
        }

        ~UiObject() {
            if (data != nullptr) {
                delete[] data;
            }
        }

        void setXValue(unsigned int vertexNumber, float value) {
            setData(vertexNumber * numberOfCoordinates, value);
        }

        void setYValue(unsigned int vertexNumber, float value) {
            setData(vertexNumber * numberOfCoordinates + 1, value);
        }

        void setZValue(unsigned int vertexNumber, float value) {
            setData(vertexNumber * numberOfCoordinates + 2, value);
        }

        unsigned int getVertexSize() const {
            return vertexSize;
        }

        const float* const getData() {
            return data;
        }

    private:
        void setData(unsigned int dataIndex, float data) {
            this->data[dataIndex] = data;
        }

    private:
        unsigned int vertexSize;
        float* data;
};

typedef std::shared_ptr<UiObject> UiObjectPtr;
typedef std::vector<UiObjectPtr> UiObjectPtrVector; 