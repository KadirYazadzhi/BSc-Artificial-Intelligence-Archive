#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include "test_data.h"
#include "colors.h"
#include "localization.h"

const char* BROKERS[] = { "John Smith", "Sarah Connor", "Michael Johnson", "Emily Davis", "David Wilson", "Jessica Taylor", "Robert Brown", "Jennifer White", "William Harris", "Elizabeth Martin" };
const int BROKERS_COUNT = 10;
const char* TYPES[] = { "Apartment", "House", "Villa", "Studio", "Penthouse", "Office", "Warehouse", "Maisonette" };
const int TYPES_COUNT = 8;
const char* AREAS[] = { "Downtown", "Suburbs", "Old Town", "Financial District", "Green Valley", "West Side", "East End", "North Hills", "South Beach", "Industrial Park" };
const int AREAS_COUNT = 10;
const char* EXPOSITIONS[] = { "North", "South", "East", "West", "North-East", "North-West", "South-East", "South-West" };
const int EXPOSITIONS_COUNT = 8;

void generateTestProperties(Node*& head) {
    std::srand(std::time(0));
    int targetCount = 30; // Sufficient for testing

    for (int i = 0; i < targetCount; ++i) {
        Node* newNode = new Node();
        Property& prop = newNode->data;

        prop.refNumber = 1000 + i + 1;
        strncpy(prop.broker, BROKERS[std::rand() % BROKERS_COUNT], 49);
        prop.broker[49] = '\0';
        strncpy(prop.type, TYPES[std::rand() % TYPES_COUNT], 49);
        prop.type[49] = '\0';
        strncpy(prop.area, AREAS[std::rand() % AREAS_COUNT], 49);
        prop.area[49] = '\0';
        strncpy(prop.exposition, EXPOSITIONS[std::rand() % EXPOSITIONS_COUNT], 19);
        prop.exposition[19] = '\0';

        prop.price = 50000.0 + (std::rand() % 450001);
        prop.totalArea = 40.0 + (std::rand() % 161);
        prop.rooms = (int)(prop.totalArea / 40) + (std::rand() % 2);
        if (prop.rooms < 1) prop.rooms = 1;
        prop.floor = 1 + (std::rand() % 15);
        prop.status = (std::rand() % 10 < 3) ? SOLD : AVAILABLE;

        newNode->next = head;
        head = newNode;
    }

    std::cout << GREEN << getTranslatedString("TEST_DATA_GENERATED_SUCCESS_PART1") << targetCount << getTranslatedString("TEST_DATA_GENERATED_SUCCESS_PART2") << RESET << std::endl;
}