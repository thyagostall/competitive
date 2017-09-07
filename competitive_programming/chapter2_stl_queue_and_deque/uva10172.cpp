#include <cstdio>
#include <stack>
#include <queue>
#include <vector>

using namespace std;

class Station: public queue<int>
{
public:
    Station(int capacity) {
        this->capacity = capacity;
    }

    bool full() {
        return this->size() == this->capacity;
    }
private:
    int capacity;
};

class Carrier: public stack<int>
{
public:
    Carrier(int capacity) {
        this->capacity = capacity;
    }

    bool full() {
        return this->size() == this->capacity;
    }
private:
    int capacity;
};

int unload(Carrier &carrier, Station &station, int station_number)
{
    int result = 0;
    while (!carrier.empty() && (!station.full() || carrier.top() == station_number)) {
        if (carrier.top() != station_number) station.push(carrier.top());
        carrier.pop();
        result++;
    }
    return result;
}

int load(Carrier &carrier, Station &station)
{
    int result = 0;
    while (!carrier.full() && !station.empty()) {
        carrier.push(station.front());
        station.pop();
        result++;
    }
    return result;
}

bool all_stations_empty(vector<Station> &stations)
{
    for (auto &s : stations) {
        if (!s.empty()) return false;
    }
    return true;
}

int main()
{
    int set, temp, cargo;

    scanf("%d", &set);
    while (set--) {
        int station_quantity, carrier_capacity, station_capacity;
        scanf("%d %d %d", &station_quantity, &carrier_capacity, &station_capacity);

        Carrier carrier(carrier_capacity);
        vector<Station> stations;
      
        stations.push_back(Station(0)); 
        for (int i = 1; i <= station_quantity; i++) {
            stations.push_back(Station(station_capacity));
            scanf("%d", &temp);

            while (temp--) {
                scanf("%d", &cargo);

                stations[i].push(cargo);
            }
        }

        int result = 0;
        int current = 1;
        while (true) {
            result += unload(carrier, stations[current], current);
            result += load(carrier, stations[current]);
            if (carrier.empty() && all_stations_empty(stations)) break;
            result += 2;
            current = current >= station_quantity ? 1 : current + 1;
        }
        printf("%d\n", result);
    }
}
