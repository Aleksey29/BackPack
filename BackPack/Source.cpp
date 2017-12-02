#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Item
{
public:
	Item(string name, int weight, int price) :name(name), weight(weight), price(price) {}
	void setName(string name) { this->name = name; }
	void setPrice(int price) { this->price = price; }
	void setWeight(int weight) { this->weight = weight; }
	string getName() { return name; }
	int getPrice() { return price; }
	int getWeight() { return weight; }
	string to_string_s()
	{
		string text;
		text += string(name);
		text += "/";
		text += to_string(price);
		text += "/";
		text += to_string(weight);
		return text;
	}

private:
	string name;
	int price;
	int weight;
};

class BackPack
{
private:
	vector<Item> bestItems;
	int maxWeight;
	int bestPrice = 0;

	int CountWeigth(vector<Item> items)
	{
		int sumW = 0;

		for (auto& it : items)
		{
			sumW += it.getWeight();
		}

		return sumW;
	}

	int CountPrice(vector<Item> items)
	{
		int sumPrice = 0;

		for (auto& it : items)
		{
			sumPrice += it.getPrice();
		}

		return sumPrice;
	}

	void CheckSet(vector<Item> items)
	{
		if (bestItems.empty())
		{
			if (CountWeigth(items) <= maxWeight)
			{
				bestItems = items;
				bestPrice = CountPrice(items);
			}
		}
		else
		{
			if (CountWeigth(items) <= maxWeight && CountPrice(items) > bestPrice)
			{
				bestItems = items;
				bestPrice = CountPrice(items);
			}
		}
	}

public:
	BackPack(int maxW) :maxWeight(maxW) {}

	void MakeAllSets(vector<Item> items)
	{
		if (!items.empty())
			CheckSet(items);
		for (int i = 0; i<items.size(); i++)
		{
			vector<Item> newSet;
			newSet = items;
			newSet.erase(newSet.begin() + i);
			MakeAllSets(newSet);
		}

	}
	vector<Item> GetBestSet()
	{
		return bestItems;
	}
};
ostream& operator<<(std::ostream& os, Item& item)
{
	return os << item.to_string_s();
}

int main()
{
	vector<Item>items;
	Item* it1 = new Item("Book", 1, 300);
	Item* it2 = new Item("Table", 4, 4000);
	Item* it3 = new Item("Mirror", 7, 150000);
	Item* it4 = new Item("Notebook", 3, 10000);
	Item* it5 = new Item("Lamp", 1, 500);
	items.push_back(*it1);
	items.push_back(*it2);
	items.push_back(*it3);
	items.push_back(*it4);
	items.push_back(*it5);
	cout << "======Set======" << endl;
	for (auto& it : items)
	{
		cout << it << endl;
	}

	BackPack backpack(8);
	backpack.MakeAllSets(items);
	if (backpack.GetBestSet().empty())
	{
		cout << "There is no solution" << endl;
	}
	else
	{
		cout << "======Best Set======" << endl;
		for (auto& it : backpack.GetBestSet())
		{
			cout << it << endl;
		}
	}
	cin.get();
	cin.get();
}