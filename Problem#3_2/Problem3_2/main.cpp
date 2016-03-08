//3_1. Реклама. В супермаркете решили оптимизировать показ рекламы. Известно расписание прихода и ухода покупателей (два целых числа). Каждому покупателю необходимо показать минимум 2 рекламы.  Рекламу можно транслировать только в целочисленные моменты времени. Покупатель может видеть рекламу от момента прихода до момента ухода из магазина. В каждый момент времени может показываться только одна реклама. Считается, что реклама показывается мгновенно. Если реклама показывается в момент ухода или прихода, то считается, что посетитель успел её посмотреть. Требуется определить минимальное число показов рекламы.

#include <iostream>
#include <vector>

//Структура покупателя
struct Customer {
    int enterTime;
    int escapeTime;
    int adReviewCount;
    int firstReviewTime;
    Customer(int enterTime, int escapeTime):enterTime(enterTime), escapeTime(escapeTime), adReviewCount(0){}
    Customer():enterTime(0), escapeTime(0), adReviewCount(0){}
};

//Перегрузка оператора для структуры
bool operator<(const Customer& left, const Customer& right) {
    return left.escapeTime < right.escapeTime;
}

//Класс магазина
class Shop {
public:
    int getMinAdCount();
    Shop(std::vector<Customer> customers) {
        this->customers = customers;
    }
private:
    std::vector<Customer> customers;
    void addAdvertisment(std::vector<Customer>::iterator from, int time);
    int adCount;
};

template <class T>
void merge(T *a, size_t a_len, T *b, size_t b_len, T *c) {
    int i = 0;
    int j = 0;

    for (; i < a_len and j < b_len;) {
        if (a[i] < b[j]) {
            c[i + j] = a[i];
            ++i;
        } else {
            c[i + j] = b[j];
            ++j;
        }
    }
    if (i == a_len) {
        for (; j < b_len; ++j) {
            c[i + j] = b[j];
        }
    } else if (j == b_len) {
        for (; i < a_len; ++i) {
            c[i + j] = a[i];
        }
    }

}

template<typename T>
void merge_sort(T array[], std::size_t size) {
    if (size > 1) {
        std::size_t const left_size = size / 2;
        std::size_t const right_size = size - left_size;
        
        merge_sort(&array[0], left_size);
        merge_sort(&array[left_size], right_size);
        
        T *tmp_array = new T[size];
        merge(array, left_size, &array[left_size], right_size, tmp_array);
        
        for (int i = 0; i < size; ++i) {
            array[i] = tmp_array[i];
        }
        
        delete [] tmp_array;
    }
}

int main() {
    //Ввод числа покупателей
    int customerCount;
    std::cin >> customerCount;
    
    //Ввод данных о покупателях
    std::vector<Customer> customers;
    for (int i = 0; i < customerCount; ++i) {
        int enterTime, escapeTime;
        std::cin >> enterTime >> escapeTime;
        customers.push_back(Customer(enterTime, escapeTime));
    }
    //Сортировка по времени выхода
    merge_sort(&customers[0], customers.size());
    
    Shop shop(customers);
    std::cout << shop.getMinAdCount();
    
    return 0;
}

int Shop::getMinAdCount() {
    //Цикл по всем покупателям
    for (std::vector<Customer>::iterator it = customers.begin() ; it != customers.end(); ++it) {
        //Если рекламу еще не смотрел - добавить рекламу в момент выхода и за 1 минуту до конца выхода
        if (it->adReviewCount == 0) {
            addAdvertisment(it, it->escapeTime);
            addAdvertisment(it ,it->escapeTime - 1);
        }
        //Если видел рекламу один раз - добавить рекламу в момент выхода
        if (it->adReviewCount == 1) {
            if (it->firstReviewTime == it->escapeTime) {
                addAdvertisment(it, it->escapeTime - 1);
            } else {
                addAdvertisment(it, it->escapeTime);
            }
        }
    }
    return adCount;
}

void Shop::addAdvertisment(std::vector<Customer>::iterator from, int time) {
    //Цикл по покупателям от текущего пока время его входа меньше времени рекламы
    for (std::vector<Customer>::iterator it = from; it != customers.end(); ++it) {
        if (it->enterTime > time) {
            break;
        }
        //Устанавливаем количество просмотров рекламы
        if (time <= it->escapeTime && time >= it->enterTime) {
            it->firstReviewTime = time;
            it->adReviewCount++;
        }
    }
    //Инкрементируем общее число показов рекламы
    adCount++;
}
