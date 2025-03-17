#include "../include/Movie.h"

#include <iostream>

Movie::Movie(const std::string& title, const std::string& genre, const size_t& releaseDate, const size_t& duration, const size_t& seatsX, const size_t& seatsY) 
	:title(title), genre(genre), releaseDate(releaseDate), duration(duration), seatsX(seatsX), seatsY(seatsY) {
	seats = 0;
	takenSeats = new TakenSeats[seats];
}

Movie::~Movie()
{
	delete[] takenSeats;
}

nlohmann::json Movie::saveAsJson() 
{
	nlohmann::json data;
	data["title"] = this->title;
	data["genre"] = this->genre;
	data["releaseDate"] = this->releaseDate;
	data["duration"] = this->duration;
	data["seatsX"] = this->seatsX;
	data["seatsY"] = this->seatsY;

	if (this->seats)
	{
		for (size_t i = 0; i < this->seats; i++)
		{
			data["takenSeats"].push_back(takenSeatsToJson(i));
		}
	}
	return data;
}

nlohmann::json Movie::takenSeatsToJson(size_t& index) 
{
	nlohmann::json data;
	data["seatX"] = this->takenSeats[index].seatX;
	data["seatY"] = this->takenSeats[index].seatY;
	data["idMemeber"] = this->takenSeats[index].idMemeber;
	return data;
}

void Movie::saveSeat(size_t seatX, size_t seatY, size_t idMemeber) 
{
	size_t odlSeats = seats;
	seats++;
	TakenSeats * newTakenSeats = new TakenSeats[seats];

	for (size_t i = 0; i < odlSeats; i++)
	{
		if (this->seatsX < seatX || this->seatsY < seatY)
		{
			std::cout << "This seat is out or range\n";

			delete[] newTakenSeats;
			seats--;
			return;
		}
		if (takenSeats[i].seatX == seatX && takenSeats[i].seatY == seatY)
		{
			std::cout << "This seat is occupied\n";

			delete[] newTakenSeats;
			seats--;
			return;
		}
		newTakenSeats[i] = takenSeats[i];
	}
	newTakenSeats[seats - 1].seatX = seatX;
	newTakenSeats[seats - 1].seatY = seatY;
	newTakenSeats[seats - 1].idMemeber = idMemeber;


	delete[] takenSeats;
	takenSeats = newTakenSeats;
}