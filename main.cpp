#include <algorithm>
#include <array>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <string>
#include <string_view>
#include <vector>

constexpr auto MAX_ITEMS = 30;

enum class Products
{
        Invalid = -1,
        productsStart,
        huaweiStart,

        HuaweiP50Pro,
        HuaweiP40Pro,
        MatePadPro,
        HuaweiWatchGT3,
        HuaweiWatchGT2,
        HuaweiFreeBudPro,
        huaweiStop,

        samsungStart,
        SamsungGalaxyS22,
        SamsungTabS8,
        SamsungNote,
        SamsungZFold,
        SamsungGalaxyBookPro,
        SamsungGalaxyProBuds,
        SamsungGalaxyWatch,
        samsungStop,

        appleStart,
        AppleIPhone12,
        AppleIPhone12Pro,
        AppleIPad,
        AppleMacBookPro,
        AppleMacbookAir,
        AppleWatch,
        AppleAirPods,
        appleStop,
        productsEnd,
        Count,
};

constexpr std::string_view PRODUCT_NAMES[static_cast<int>(Products::Count)] = {
    [static_cast<int>(Products::AppleIPhone12)]        = "AppleIPhone12",
    [static_cast<int>(Products::AppleIPhone12Pro)]     = "AppleIPhone12Pro",
    [static_cast<int>(Products::AppleIPad)]            = "AppleIPad",
    [static_cast<int>(Products::AppleMacBookPro)]      = "AppleMacBookPro",
    [static_cast<int>(Products::AppleMacbookAir)]      = "AppleMacbookAir",
    [static_cast<int>(Products::AppleAirPods)]         = "AppleAirPods",
    [static_cast<int>(Products::AppleWatch)]           = "AppleWatch",
    [static_cast<int>(Products::SamsungGalaxyS22)]     = "SamsungGalaxyS22",
    [static_cast<int>(Products::SamsungTabS8)]         = "SamsungTabS8",
    [static_cast<int>(Products::SamsungNote)]          = "SamsungNote",
    [static_cast<int>(Products::SamsungZFold)]         = "SamsungZFold",
    [static_cast<int>(Products::SamsungGalaxyBookPro)] = "SamsungGalaxyBookPro",
    [static_cast<int>(Products::SamsungGalaxyProBuds)] = "SamsungGalaxyProBuds",
    [static_cast<int>(Products::SamsungGalaxyWatch)]   = "SamsungGalaxyWatch",
    [static_cast<int>(Products::HuaweiP50Pro)]         = "HuaweiP50Pro",
    [static_cast<int>(Products::HuaweiP40Pro)]         = "HuaweiP40Pro",
    [static_cast<int>(Products::MatePadPro)]           = "MatePadPro",
    [static_cast<int>(Products::HuaweiWatchGT3)]       = "HuaweiWatchGT3",
    [static_cast<int>(Products::HuaweiWatchGT2)]       = "HuaweiWatchGT2",
    [static_cast<int>(Products::HuaweiFreeBudPro)]     = "HuaweiFreeBudPro",

};

// std::vector<std::string> PRODUCT_NAMES {
//          "Huawei P50 Pro",
//          "Huawei P40 Pro",
//          "Mate Pad Pro",
//          "Huawei Watch GT3",
//          "Huawei Watch GT2",
//          "Huawei FreeBud Pro",
//          "Samsung Galaxy S22",
//          "Samsung Tab S8",
//          "Samsung Note",
//          "Samsung ZFold",
//          "Samsung Galaxy BookPro",
//          "Samsung Galaxy ProBuds",
//          "Samsung GalaxyWatch",
//           "Apple IPhone12",
//           "Apple Iphone Pro12",
//           "Apple IPad",
//           "Apple MacBookPro",
//           "Apple MacbookAir",
//           "Apple AirPods",
//           "Apple Watch",

// };

constexpr auto is_valid_product(Products prod) { return prod > Products::Invalid && prod < Products::Count; }

constexpr auto get_product_name(Products prod)
{
        if (!is_valid_product(prod)) { return std::string_view {""}; }

        return PRODUCT_NAMES[static_cast<int>(prod)];
}

auto list_products()
{
        std::cout << "Product list: \n";
        std::for_each_n(std::begin(PRODUCT_NAMES), std::size(PRODUCT_NAMES), [i = 0](const auto& name) mutable {
                std::printf("(%d) %s\n", i, name.data());
                i++;
        });
        std::printf("---------------\n");
}

struct Item
{
        Products    product;
        int         stock;
        float       price;
        std::string name;

        Item() = default;
        Item(Products p, int num_stock, float price, std::string_view name) : product {p}, stock {num_stock}, price {price}, name {name} {}
};
struct Inventory
{
        using SearchPredicate = std::function<bool(const Item&)>;
        using Items           = std::vector<Item>;
        using ItemPtr         = Items::iterator;

        Items items;

        Inventory() { items.reserve(MAX_ITEMS); }

        auto add(const Item& item) { items.emplace_back(item); }

        auto remove(ItemPtr pitem) { items.erase(pitem); }

        auto search(const SearchPredicate& pred) -> ItemPtr
        {
                auto pitem = std::find_if(items.begin(), items.end(), pred);
                if (pitem != items.end()) { return pitem; }
                return {};
        }
};

Inventory inventory;

auto      Brand_product(Products p)
{
        return p > Products::productsStart && p < Products::productsEnd;        // why do we need 2 &
}

auto Brand_apple_product(Products p) { return p > Products::appleStart && p < Products::appleStop; }
auto Brand_samsung_product(Products p) { return p > Products::samsungStart && p < Products::samsungStop; }
auto Brand_huwaei_product(Products p) { return p > Products::huaweiStart && p < Products::huaweiStop; }

auto edit_Item_Product(const Inventory::Items& items)
{
        do {
                char option {};
                std::cout << "(n)Search by Name, (p)Search by Product Id: ";
                std::cin >> option;
                Inventory::ItemPtr pitem;
                if (option == 'n')
                {
                        list_products();
                        std::string name {};
                        std::cout << "Enter product name: ";
                        std::cin >> name;

                        return std::find_if(items.begin(), items.end(),
                                            [&](const Item& item) { return item.name == name; });        // why do we need the [&]
                }
                else if (option == 'p')
                {
                        list_products();
                        Products prod {Products::Invalid};
                        std::printf("Select product id: ");
                        std::scanf("%d", &prod);
                        std::printf("Selected product category: %s\n", get_product_name(prod).data());
                        pitem = inventory.search([&](const Item& item) { return item.product == prod; });
                }

                return items.end();

        } while (true);
}

// auto remove_product()
//{

// std::for_each(items.begin(), items.end(), [](const auto& n) { std::cout << pitem->name << '\n'; });
// print items in nums
//  }

auto get_product_details()
{
        Item item {};

        int  product_id {};
        do {
                list_products();
                std::cout << "Select Product category"
                          << "\n";
                int Product_num {};
                std::scanf("%d", &item);
                std::cout << "Select product Id: ";
                std::cin >> product_id;
                if (Brand_product(static_cast<Products>(product_id)))
                {
                        std::cout << "Enter stock: ";
                        std::cin >> item.stock;
                        std::cout << "Enter price: ";
                        std::cin >> item.price;
                        std::cout << "Enter name: ";
                        std::getline(std::cin >> std::ws, item.name);

                        // std::cin >> item.name;
                        return item;
                }

                else if (!is_valid_product(item.product))
                {
                        std::cout << "Invalid Option"
                                  << "\n";
                }

        } while (true);
}

// using Items = std::vector<Item>;

// auto Add_item_option()
// {
//         Item item {};
// do{
//         list_products();
//         int Product_num;
//         auto get_product_details()

// }
// }

auto search_item(const Inventory::Items& items)
{
        do {
                char option {};
                std::cout << "(n)Search by Name, (p)Search by Product Id: ";
                std::cin >> option;
                Inventory::ItemPtr pitem;
                if (option == 'n')
                {
                        list_products();
                        std::string name {};
                        std::cout << "Enter product name: ";
                        std::cin >> name;

                        return std::find_if(items.begin(), items.end(),
                                            [&](const Item& item) { return item.name == name; });        
                }
                else if (option == 'p')
                {
                        list_products();
                        Products prod {Products::Invalid};
                        std::printf("Select product id: ");
                        std::scanf("%d", &prod);
                        std::printf("Selected product category: %s\n", get_product_name(prod).data());
                        pitem = inventory.search([&](const Item& item) { return item.product == prod; });
                        return items.end();
                }
        } while (true);
}

auto main() -> int
{
        Inventory::Items items {};

        char             opt {};
        do {
                std::cout << "(a)Add, (r)Remove, (e)Edit, (s)Search, (c) Checkout: ";
                // std::scanf(" %c", &opt);
                std::cin >> opt;

                if (opt == 'a')
                {
                        const auto item = get_product_details();

                        items.push_back(item);
                }
                else if (opt == 's')
                {
                        const auto pitem = search_item(items);
                        std::cout << pitem->name << '\n';
                }

                else if (opt == 'e')
                {
                        std::cout << "Please Search for item: "
                                  << "\n";
                        auto pitem = search_item(items);
                        std::cout << "Choose 'a' to Add or 'r' to Remove"
                                  << "\n";
                        char opt {};
                        // get input from user for opt
                        std::cin>>opt;
                        if (opt == 'a')
                        {
                                const auto add_item = get_product_details();
                                inventory.add(add_item);
                        }
                        else if (opt == 'r')

                        {
                                items.erase(pitem);
                                std::for_each(items.begin(), items.end(), [&](const Item& item) { std::cout << pitem->name << '\n'; });
                                std::cout<<"--------------\n";
                                std::cout<<"Item Erased\n";
                        }
                   
                }
                else if (opt=='r')
                {
                                std::cout<<"Please search for the item that you would like to remove!!\n"
                                <<"-------------------\n";
                                auto pitem=search_item(items);
                                items.erase(pitem);
                                std::for_each(items.begin(), items.end(), [&](const Item& item) { std::cout << pitem->name << '\n'; });
                                std::cout<<"Item Erased\n";
                }

                else if (opt=='c')
                {  
                         std::cout<<"******************\n";
                        std::cout<<"Thansks for Shopping with us !!\n";
                        break;


                }
                else
                {
                        std::cout << "Invalid option selected. Please try again." << '\n';
                        break;
                }
        } while (true);
}

// enum class Brands
//  {
//          Apple,
//          Samsung,
//          Huawei,
//          Count,
//  };

// auto get_brand_from_user()
// {

// }

// constexpr std::string_view BRAND_NAMES[static_cast<int>(Brands::Count)] = {
//     [static_cast<int>(Brands::Apple)]   = "Apple",
//     [static_cast<int>(Brands::Huawei)]  = "Huawei",
//     [static_cast<int>(Brands::Samsung)] = "Samsung",
// };

// //  using BrandNames = std::string_view[static_cast<int>(Brands::Count)];
// //  constexpr auto get_brand_name(Brands p) { return BRAND_NAMES[static_cast<int>(p)].data(); }
// constexpr auto print_message()
// {
//         std::printf("Select Brands (%d: %s, %d: %s, %d: %s): ",
//                 static_cast<int>(Brands::Apple),
//                 BRAND_NAMES[static_cast<int>(Brands::Apple)].data(),
//                 static_cast<int>(Brands::Huawei),
//                 BRAND_NAMES[static_cast<int>(Brands::Huawei)].data(),
//                 static_cast<int>(Brands::Samsung),
//                 BRAND_NAMES[static_cast<int>(Brands::Samsung)].data());
// };

// enum class Huawei
// {
//         HuaweiP50Pro,
//         HuaweiP40Pro,
//         MatePadPro,
//         HuaweiWatchGT3,
//         HuaweiWatchGT2,
//         HuaweiFreeBudPro,
//         Count,
// };

// struct Item
// {
//         Product product;
//         float  price;
// };

// constexpr std::string_view PRODUCT_NAMES[static_cast<int>(Huawei::Count)] = {
//     [static_cast<int>(Huawei::HuaweiP50Pro)] = "HuaweiP50Pro",     [static_cast<int>(Huawei::HuaweiP40Pro)] = "HuaweiP40Pro",
//     [static_cast<int>(Huawei::MatePadPro)] = "MatePadPro",         [static_cast<int>(Huawei::HuaweiWatchGT3)] = "HuaweiWatchGT3",
//     [static_cast<int>(Huawei::HuaweiWatchGT2)] = "HuaweiWatchGT2", [static_cast<int>(Huawei::HuaweiFreeBudPro)] = "HuaweiFreeBudPro",

// };
// using ProductNames = std::string_view[static_cast<int>(Huawei::Count)];
// constexpr auto get_product_name(Huawei p) { return PRODUCT_NAMES[static_cast<int>(p)].data(); }
// constexpr auto print_message()
// {
//         std::printf("Select Huwawei Product (%d: %s, %d: %s, %d: %s,%d: %s,%d: %s,%d: %s): ", static_cast<int>(Huawei::HuaweiP50Pro),
//                     PRODUCT_NAMES[static_cast<int>(Huawei::HuaweiP50Pro)].data(), static_cast<int>(Huawei::HuaweiP40Pro),
//                     PRODUCT_NAMES[static_cast<int>(Huawei::HuaweiP40Pro)].data(), static_cast<int>(Huawei::MatePadPro),
//                     PRODUCT_NAMES[static_cast<int>(Huawei::MatePadPro)].data(), static_cast<int>(Huawei::HuaweiWatchGT3),
//                     PRODUCT_NAMES[static_cast<int>(Huawei::HuaweiWatchGT3)].data(), static_cast<int>(Huawei::HuaweiWatchGT2),
//                     PRODUCT_NAMES[static_cast<int>(Huawei::HuaweiWatchGT2)].data(), static_cast<int>(Huawei::HuaweiFreeBudPro),
//                     PRODUCT_NAMES[static_cast<int>(Huawei::HuaweiFreeBudPro)].data());
// }

// auto print_item(const Item& item)
// {
//         std::cout << "Product: " << get_product_name(item.product) << '\n';
//         std::cout << "Price: " << item.price << '\n';
// }

// auto main() -> int
// {
//         print_message();

//         int opt {};
//         std::cin >> opt;

//         std::cout << PRODUCT_NAMES[opt] << "\n";
//         if (opt == 0)
//         {
//                 Item HuaweiP50Pro {};
//                 HuaweiP50Pro.product = Huawei::HuaweiP50Pro;
//                 HuaweiP50Pro.price   = 500;        // USD
//                 print_item(HuaweiP50Pro);
//         }
//         else if (opt == 1)
//         {
//                 Item HuaweiP40Pro {};
//                 HuaweiP40Pro.product = Huawei::HuaweiP40Pro;
//                 HuaweiP40Pro.price   = 400;
//                 print_item(HuaweiP40Pro);
//         }
//         else if (opt == 2)
//         {
//                 Item MatePad {};
//                 MatePad.product = Huawei::MatePadPro;
//                 MatePad.price   = 650;
//                 print_item(MatePad);
//         }
//         else if (opt == 3)
//         {
//                 Item HuaweiWatchGT3 {};
//                 HuaweiWatchGT3.product = Huawei::HuaweiWatchGT3;
//                 HuaweiWatchGT3.price   = 220;
//                 print_item(HuaweiWatchGT3);
//         }
//         else if (opt == 4)
//         {
//                 Item HuaweiWatchGT2 {};
//                 HuaweiWatchGT2.product = Huawei::HuaweiWatchGT2;
//                 HuaweiWatchGT2.price   = 150;
//                 print_item(HuaweiWatchGT2);
//         }
//         else if (opt == 5)
//         {
//                 Item HuaweiFreeBudPro {};
//                 HuaweiFreeBudPro.product = Huawei::HuaweiFreeBudPro;
//                 HuaweiFreeBudPro.price   = 130;
//                 print_item(HuaweiFreeBudPro);
//         }
//         else { std::cout << "Invalid Entry Please try again!!" << std::endl; }
// }

// auto main() -> int
//{

// enum class brand{
//    Apple,
//    Huawei,
//     Samsung
//  };
//  enum class apple
//  {
//     Iphone_Pro = 1000,
//      IPad = 1000,
//      Macbook Air,

//  };

//     constexpr std::vector< >Huawei = {
// "\n1= Huawei P50 Pro       $500\n2= Huawei P40 Pro       $400\n3= MatePad Pro          $650\n4= Huawei Watch GT 3    $220\n5= Huawei Watch
// GT 2 $150\n6= Huawei FreeBuds Pro  $130\n"}; std::string Apple   = ;

//     double HuaweiP50Pro;
//     double HuaweiP40Pro;
//     double MatePadPro;
//     double HuaweiWatchGT3;
//     double HuaweiWatchGT2;
//     double HuaweiFreeBudPro;

//     // product Products;
//     // int number_of_items=0;

//     int opt  = 0;
//     int opt2 = 0;

//     double Balance = 100000;
//     std::string Huawei =
//     "\n1= Huawei P50 Pro       $500\n2= Huawei P40 Pro       $400\n3= MatePad Pro          $650\n4= Huawei Watch GT 3    $220\n5= Huawei
//     Watch GT 2 $150\n6= Huawei FreeBuds Pro  $130\n"; std::string Apple   =
//     "\n 1= MacBook Pro 2020  $1500\n 2= MacBook Air 2022  $1300\n 3= iPhone Pro 12      $700\n 4= iPhone Pro Max 12  $800\n 5= iPad Pro
//     2022 $1000\n 6= AirPods Pro 2     $250\n 7= Apple Magic Mouse  $100\n 8= Apple Watch        $350"; std::string  SamsungModels =
//         "\n 1= Samsung Galaxy S22        $850\n 2= Samsung Galaxy Zfold     $1000\n 3= Samsung Tab S8            $600\n 4= Samsung Tab S8
//         Ultra $750\n 5= Samsung Galaxy Book Pro  $1500\n 6= Samsung Galaxy Watch      $250\n 7= Samsung Galaxy Pro Buds   $150";
//     std::cout<<"select brand:  "<<"\n"<<"1: Huawei"<<"\n"<<"2: Apple"<<"\n"<<"3: Samsung"<<std::endl;
//    std::cin>>opt;
//     do
//     {
//     if(opt==1)
//     {
//         //std::cout<<HuaweiP50Pro<<"1= Huawei P50 Pro \t$500\n"<<HuaweiP40Pro<<"2= Huawei P40 Pro       $400\n"<<MatePadPro<<"3= MatePad
//         Pro $650\n"<<HuaweiWatchGT3<<"4= Huawei Watch GT 3    $220\n"<<HuaweiWatchGT2<<"5= Huawei Watch GT 2 $150\n"<<HuaweiFreeBudPro<<"6=
//         Huawei FreeBuds Pro  $130\n";

//         std::cout <<Huawei<<"\n";
//         std::cout<<"please select the desired device:  "<<"\n";
//         std::cin>>opt;
//         if(opt==1)
//         {
//             HuaweiP50Pro++;
//             std::cout<<"Huawei P50 Pro\t$500"<<"\n";
//         }
//         if(opt==2)
//         {
//             HuaweiP40Pro++;
//             std::cout<<"Huawei P40 Pro\t$400"<<"\n";

//         }
//         if(opt==3)
//         {
//             MatePadPro++;
//             std::cout<<"Matepod Pro\t$650"<<"\n";
//         }
//         if(opt==4)
//         {
//             HuaweiWatchGT3;
//             std::cout<<"Huawei Watch GT3\t$220"<<"\n";
//         }
//         if(opt==5)
//         {
//             HuaweiWatchGT2++;
//             std::cout<<"Huawei Watch GT2\t$150"<<"\n";
//         }
//         if(opt==6)
//         {
//             HuaweiFreeBudPro++;
//             std::cout<<"Huawei P40 Pro\t$130"<<"\n";
//         }
//     }
//     else if(opt==2)
//     {
//         std::cout <<Apple<<std::endl;
//         std::cout<<"please select the desired device:  "<<"\n";
//         std::cin>>opt;
//         if(opt==1)
//         {

//         }
//     }
//     else if(opt==3)
//     {
//         std::cout <<SamsungModels<<std::endl;
//     }
//     else
//     {
//         std::cout<<"wrong input: ";
//         continue;
//     }
//     break;
//             }while (true);
//}

//        {
//                 if (uop == 0) { break; }

//                 if (uop > 4 && uop < MAX_OPERATIONS)
//                 {
//                         // user probably wants to add new functions
//                         if (ops.size() < (MAX_OPERATIONS + 1))
//                         {
//                                 std::cout << "(p)Pow, (r)Rem: ";
//                                 char selection {};
//                                 std::cin >> selection;
//                                 if (selection == 'p') { ops.push_back(std::pow); }
//                                 else if (selection == 'r') { ops.push_back(std::fmod); }
//                         }
//                 }
//                 else
//                 {
//                         std::cout << "Invalid operation selected. Please try again!";
//                         continue;
//                 }
//