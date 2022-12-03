//
// Created by Pablo Moreno on 12/3/22.
//

#ifndef COVID_PLUS_PLUS_ROW_H
#define COVID_PLUS_PLUS_ROW_H

class Row {
private:
    int day;
    int month;
    int year;
    int cases;
    int deaths;
    string country;
    int rate;
public:
    Row(int day, int month, int year, int cases, int deaths, const string &country, int rate);

    int getDay() const;

    int getMonth() const;

    int getYear() const;

    int getCases() const;

    int getDeaths() const;

    const string &getCountry() const;

    int getRate() const;
};

Row::Row(int day, int month, int year, int cases, int deaths,
         const std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>> &country, int rate)
        : day(day), month(month), year(year), cases(cases), deaths(deaths), country(country), rate(rate) {}

int Row::getDay() const {
    return day;
}

int Row::getMonth() const {
    return month;
}

int Row::getYear() const {
    return year;
}

int Row::getCases() const {
    return cases;
}

int Row::getDeaths() const {
    return deaths;
}

const std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>> &Row::getCountry() const {
    return country;
}

int Row::getRate() const {
    return rate;
}

#endif //COVID_PLUS_PLUS_ROW_H
