#include <algorithm>

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <iostream>
using std::getline;
using std::cin;
using std::cout;

#include <map>
using std::map;
using std::pair;

#include <sstream>
using std::istringstream;

void print_store_info(vector<pair<string, int>> &store_list) {
    cout << "Store Related Information (ordered by in-file order):" << std::endl;
    cout << "There are " << store_list.size() << " store(s)." << std::endl;
    for (pair<string, int> store_items : store_list) {
        cout << store_items.first << " has " << store_items.second << " distinct items." << std::endl;
    }
    cout << std::endl;
}

bool item_by_alpha(pair<string, int> pair1, pair<string, int> pair2) {
    return pair1.first < pair2.first;
}

bool item_by_value(pair<string, int> pair1, pair<string, int> pair2) {
    return pair1.second < pair2.second;
}

void print_item_information(map<string, int> item_quantities) {
    vector<pair<string, int>> item_list;
    std::copy(item_quantities.begin(), item_quantities.end(), std::back_inserter(item_list));
    std::sort(item_list.begin(), item_list.end(), item_by_alpha);
    cout << "Item Related Information (ordered alphabetically):" << std::endl;
    cout << "There are " << item_quantities.size() << " distinct item(s) available for purchase." << std::endl;
    for (auto item_pair : item_list) {
        cout << "There are " << item_pair.second << " " << item_pair.first << "(s)." << std::endl;
    }
    cout << std::endl;
}
/*
vector<pair<string, double>> get_cheapest_stores(string &item_req, map< string, map< string, double > > &store_items_w_prices) {
    vector<pair<string, double>> item_list;
    std::copy(store_items_w_prices.begin(), store_items_w_prices.end(), std::back_inserter(item_list));
    std::sort(item_list.begin(), item_list.end(), item_by_value);
    return item_list;
}
*/
void print_shopping_trip(map< string, int> &item_locations, vector<pair<string, int>> shopping_list) { // map< string, map< string, int > > &store_items_w_quantities, map< string, map< string, double > > &store_items_w_prices, map<string, string> &store_locations,
    vector<pair<string, int>> cheapest_stores;
    //double total_price = 0.0;
    cout << "Shopping:" << std::endl;
    for (auto item_req : shopping_list) {
        cout << "Trying to order " << item_req.second << " " << item_req.first << "(s)." << std::endl;
        cout << item_locations[item_req.first] << " store(s) sell " << item_req.first << "." << std::endl;
        //cheapest_stores = get_cheapest_stores(item_req, store_items_w_prices);
        //for (auto price_pair : cheapest_stores) {

        //}
    }
}

int main() {
    cout.flush();

    string line;
    bool first_store = true;
    bool first_item = true;
    bool name_processed = false;
    bool location_processed = false;

    vector< pair< string, int> > store_list;

    string name;
    string location;

    int num_stores = 0;
    int stores_processed = 0;
    int num_shop_items = 0;
    int shop_items_processed = 0;

    map< string, map< string, int > > store_items_w_quantities;
    map< string, map< string, double > > store_items_w_prices;
    map<string, string> store_locations;

    map< string, int> item_quantities;
    map< string, int> item_locations;

    string item;
    double quantity;
    double price;
    bool store_data_done = false;

    vector<pair<string, int>> shopping_list;

    while (getline(cin, line)) {
        if (first_store == true) {
            first_store = false;
            num_stores = line[0] - '0';

        } else if (line == "") {
            name_processed = false;
            location_processed = false;
            stores_processed++;
            store_list.push_back(pair<string, int>(name, store_items_w_quantities[name].size()));


        } else if (stores_processed < num_stores) {
            if (name_processed == false) {
                name = line;
                name_processed = true;
            } else if (location_processed == false) {
                location = line;
                location_processed = true;
                store_locations.insert(pair<string, string>(name, location));
                store_items_w_quantities[name]; // create this name key in map
                store_items_w_prices[name];

            } else {
                istringstream iss(line);
                vector<string> vals;
                while (iss.good()) {
                    string sub;
                    getline(iss, sub, ',');
                    vals.push_back(sub);
                }
                item = vals[0];
                quantity = std::stoi(vals[1]);
                price = std::stod(vals[2].substr(1, string::npos));
                
                store_items_w_quantities[name].insert(pair<string, int>(item, quantity));
                store_items_w_prices[name].insert(pair<string, double>(item, price));

                if ( item_quantities.find(item) == item_quantities.end() ) {
                    item_quantities.insert(pair<string, int>(item, quantity));
                    item_locations.insert(pair<string, int>(item, 1));
                } else {
                    item_quantities[item] += quantity;
                    item_locations[item]++;
                }
                
            }
        } else {
            store_data_done = true;
        }
        
        if (store_data_done == true) {
            if (first_item == true) {
                first_item = false;
                num_shop_items = line[0] - '0';
            } else if (shop_items_processed < num_shop_items) {
                istringstream iss(line);
                iss >> quantity;
                iss >> item;
                shopping_list.push_back(pair<string, int>(item, quantity));
            }
        }
    
    }
    print_store_info(store_list);
    print_item_information(item_quantities);
    print_shopping_trip(item_locations, shopping_list);


}