#include "knapsack.h"

#include <algorithm>
#include <iostream>

namespace knapsack {

int maximum_value(int max_weight, std::vector<Item> items){

    const int rows = items.size() + 1;
    const int cols = max_weight + 1;
    int max{};

    // sort by weight
    std::sort(items.begin(), items.end(), 
                                        [] (auto e1, auto e2)
                                        { 
                                            return e2.weight < e1.weight;

                                        });

    std::vector<std::vector<int>> table(rows, std::vector<int>(cols, 0));

    for (int i{1}; i < rows; i++) {

        for (int j{}; j < cols; j++) {

            int* table_element = &table[i][j];

            // init
            if (i == 0) {
                *table_element = 0;

            } else {

                auto item_element = items[i-1];
                auto item_weight = item_element.weight;
                auto item_value = item_element.value;

                if (item_weight > j) {
                    *table_element = table[i-1][j];
                } else {

                    *table_element  = std::max(table[i-1][j], 
                        (j - item_weight) >= 0 ? 
                        table[i-1][j-item_weight] + item_value
                        :
                        item_value
                    );

                    if (*table_element > max) {
                        max = *table_element;
                    }
 
                }

            }

        }
    }









   /*  int max{};
    int running_max{};
    int weight{};
    
    // sort by weigh/value descending
    std::sort(items.begin(), items.end(), 
                                        [] (auto e1, auto e2)
                                        { 
                                            return (e2.value / e2.weight) <
                                                   (e1.value / e1.weight);

                                        });

     
    std::for_each(items.begin(), items.end(), 
                                            [] (auto e) 
                                            {
                                                std::cout << e.value << ", " << e.weight << ", " 
                                                        << e.value / e.weight << std::endl;
                                            }); 

    std::cout << std::endl;                                                      
    // pick until max_weight is reached, safe in variable
    for (std::size_t i{}; i < items.size(); i++) {

        running_max = 0;
        weight = 0;

        for (std::size_t j{i}; j < items.size(); j++) {

            auto elem = items[j];
            auto elem_weight = elem.weight;
            auto elem_value = elem.value;

            weight += elem_weight;

            if (weight > max_weight) {
                
                if (running_max > max) {
                    max = running_max;
                }

                break;

            } else {
                running_max += elem_value;

                // last element
                // perform additional check 
                if (j == items.size()-1) {
                    if (running_max > max) {
                        max = running_max;
                    }
                }
            }


        }

    }
 */
    
    return max;

}

}  // namespace knapsack
