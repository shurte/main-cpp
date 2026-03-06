#pragma once

class UiObject {
    public:
        UiObject()
            : data(new float[4 * 3])
            , vertexSize(4) {

        }

        UiObject(const UiObject& rhs)
            : data(new float[4 * 3])
            , vertexSize(4) {
                data[0] = rhs.data[0];
                data[1] = rhs.data[1];
                data[2] = rhs.data[2];
                data[3] = rhs.data[3];
                data[4] = rhs.data[4];
                data[5] = rhs.data[5];
                data[6] = rhs.data[6];
                data[7] = rhs.data[7];
                data[8] = rhs.data[8];
                data[9] = rhs.data[9];
                data[10] = rhs.data[10];
                data[11] = rhs.data[11];
        }

        ~UiObject() {
            if (data != nullptr) {
                delete[] data;
            }
        }

        void setData(unsigned int dataIndex, float data) {
            this->data[dataIndex] = data;
        }

        unsigned int getVertexSize() const {
            return vertexSize;
        }

        float* getData() {
            return data;
        }

    public:
        float* data;
        unsigned int vertexSize;
};
