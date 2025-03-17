#pragma once

#include <string>
#include <nlohmann/json.hpp>

struct TakenSeats
{
	size_t seatX;
	size_t seatY;
	size_t idMemeber;
};

class Movie
{
public:
	Movie(const std::string& title = "", const std::string& genre = "", const size_t& releaseDate = 0, const size_t& duration = 0, const size_t& seatsX = 0, const size_t& seatsY = 0);
	~Movie();

	nlohmann::json saveAsJson();
	void saveSeat(size_t seatX, size_t seatY, size_t idMemeber);

private:
	std::string title;
	std::string genre;

	size_t releaseDate;
	size_t duration;
	size_t seatsX;
	size_t seatsY;

	size_t id;
	size_t seats;
	TakenSeats* takenSeats;

	nlohmann::json takenSeatsToJson(size_t& index);
};