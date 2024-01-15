/**
 * @file ring_buffer.h
 * @author Forairaaaaa
 * @brief
 * @version 0.1
 * @date 2024-01-12
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <cstddef>
#include <functional>
// Refs:
// https://en.wikipedia.org/wiki/Circular_buffer

namespace SmoothUIToolKit
{
    template <typename T, size_t Capacity>
    class RingBuffer
    {
    public:
        struct Config_t
        {
            bool allowOverwrite = false;
        };

    private:
        struct Data_t
        {
            T* buffer = nullptr;
            size_t w_index = 0;
            size_t r_index = 0;
        };
        Data_t _data;
        Config_t _config;

    public:
        RingBuffer() { _data.buffer = new T[Capacity]; }
        ~RingBuffer() { delete _data.buffer; }

        inline Config_t& setConfig() { return _config; }
        inline const Config_t& getConfig() { return _config; }

        inline void allowOverwrite(bool allow) { _config.allowOverwrite = allow; }

        inline bool isFull() { return (_data.w_index + 1) % Capacity == _data.r_index; }
        inline bool isEmpty() { return _data.r_index == _data.w_index; }

        inline size_t size() { return Capacity; }

        bool put(const T& value)
        {
            if (isFull())
            {
                // If allow overwrite, push read index
                if (_config.allowOverwrite)
                    _data.r_index = (_data.r_index + 1) % Capacity;
                else
                    return false;
            }

            _data.buffer[_data.w_index] = value;
            _data.w_index = (_data.w_index + 1) % Capacity;
            return true;
        }

        bool get(T& value)
        {
            if (isEmpty())
                return false;

            value = _data.buffer[_data.r_index];
            _data.r_index = (_data.r_index + 1) % Capacity;
            return true;
        }

        bool getAll(std::function<void(T)> valueCallback)
        {
            if (isEmpty())
                return false;

            T temp;
            while (!isEmpty())
            {
                get(temp);
                valueCallback(temp);
            }
            return true;
        }

        bool peek(T& value)
        {
            if (isEmpty())
                return false;

            value = _data.buffer[_data.r_index];
            return true;
        }

        bool peekAll(std::function<void(T)> valueCallback)
        {
            if (isEmpty())
                return false;

            size_t peek_index = _data.r_index;
            while (peek_index != _data.w_index)
            {
                valueCallback(_data.buffer[peek_index]);
                peek_index = (peek_index + 1) % Capacity;
            }
            return true;
        }
    };
} // namespace SmoothUIToolKit
