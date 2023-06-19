//An example from github for a singleton logger from https://github.com/CallToPowerLegacy/cpp-logger-singleton by author Denis Meyer
//  main and several header and cpp files combined togher 



/**
 * Logger (Singleton) test
 * @description Logger test suite
 * @author Denis Meyer
 * @website https://sites.google.com/site/calltopowersoftware/software
 * @version 1.0.0
 * @created 3/16/11
 * @file main.cpp
 *
 *  Copyright (C) 2014 Denis Meyer, calltopower88@googlemail.com
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#include <iostream>
#include <string>
#include <string>
#include <iostream>
#include <ostream>
#include <stdlib.h>
#include <stdarg.h>

 /**
  * Logger (Singleton) Header
  * @description a Logger implementing the Singleton pattern
  * @author Denis Meyer
  * @website https://sites.google.com/site/calltopowersoftware/software
  * @version 1.0.0
  * @created 3/16/11
  * @file Logger.h
  *
  *  Copyright (C) 2014 Denis Meyer, calltopower88@googlemail.com
  *  This program is free software; you can redistribute it and/or modify
  *  it under the terms of the GNU General Public License as published by
  *  the Free Software Foundation; either version 2 of the License, or
  *  (at your option) any later version.
  *
  *  This program is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License along
  *  with this program; if not, write to the Free Software Foundation, Inc.,
  *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
  */
#ifndef LOGGER_H
#define LOGGER_H



  /**
   * Logger Singleton
   */
class Logger
{
public:
    /**
     * returns the Logger instance
     * @return the Logger instance
     */
    static Logger* instance();

    /*************************************************
     * helper
     *************************************************/

     /**
      * prints nr newlines
      * @param nr number of newlines ot print
      */
    void newLine(const int nr = 1) const;

    /**
     * prints str times times
     * @param times number of times to print str
     * @param str str to print times times
     * @param separator flag if current separator should be used or not
     */
    void printTimes(const int times, const std::string str, const bool separator = false) const;

    /*************************************************
     * logging
     *************************************************/

     /**
      * logs a std::string
      * @param a std::string to log
      */
    bool log(const std::string str = "") const;

    /**
     * logs an int
     * @param an int
     */
    bool log(const int i) const;

    /**
     * logs a double
     * @param a double
     */
    bool log(const double d) const;

    /**
     * logs a double**
     * @param a double**
     */
    bool log(double** d, const int rows, const int cols) const;

    /**
     * logs a variable number of arguments
     * @param variable number of arguments to log
     *      - f or d:   float and double
     *      - c     :   char
     *      - s     :   string (char *)
     *      - i     :   integer
     *      - b     :   bool
     * @return number of arguments logged
     */
    int logX(const std::string szTypes = "", ...) const;

    /*************************************************
     * setter
     *************************************************/

     /**
      * sets a prefix
      * @param prefix to set before every log
      */
    void setPrefix(const std::string prefix = "");

    /**
     * sets a postfix
     * @param postfix to set after every log
     */
    void setPostfix(const std::string postfix = "");

    /**
     * sets a separator
     * @param separator to set between multiple arguments
     */
    void setSeparator(const std::string separator = " ");

    /**
     * sets flag if output to stream
     * @param flag if output to stream
     */
    void setOutput(const bool output = true);

    /**
     * sets flag if endline after each log
     * @param flag if endline after each log
     */
    void setEndline(const bool endline = true);

    /**
     * sets if output to stream
     * @param flag if output to stream
     */
    void setStream(std::ostream& stream = std::cout);

    /*************************************************
     * clearer/resetter
     *************************************************/

     /**
      * resets the number of successful logs
      */
    void resetNrOfLogs();

    /**
     * clears the prefix
     */
    void clearPrefix();

    /**
     * clears the postfix
     */
    void clearPostfix();

    /**
     * resets the separator
     */
    void resetSeparator();

    /*************************************************
     * getter
     *************************************************/

     /**
      * returns the successful number of logs
      * @return the successful number of logs
      */
    unsigned int getNrOfLogs() const;

    /**
     * returns the prefix
     * @return the prefix
     */
    std::string getPrefix() const;

    /**
     * returns the postfix
     * @return the postfix
     */
    std::string getPostfix() const;

    /**
     * returns the separator
     * @return the separator
     */
    std::string getSeparator() const;

    /**
     * returns a flag if output
     * @return true if output, false else
     */
    bool output() const;

    /**
     * returns a flag if endl after each log set
     * @return true if endl after each log set, false else
     */
    bool endl() const;

private:
    /**
     * default ctor
     */
    Logger();

    /**
     * copy ctor
     */
    Logger(const Logger& l);

    /**
     * dtor
     */
    ~Logger();

    /**
     * assignment operator
     */
    Logger& operator=(const Logger& l);

    // static variables
    static Logger* m_instance;
    static std::string m_prefix;
    static std::string m_postfix;
    static std::string m_separator;
    static bool m_output;
    static bool m_endl;
    static std::ostream* m_stream;
    static unsigned int m_nrLogs;

    // union for multiple argument logging
    mutable union currType_t
    {
        int i;
        float f;
        char c;
        char* s;
    } m_currType;
};

#endif // LOGGER_H




 /**
  * Logger (Singleton) Source
  * @description a Logger implementing the Singleton pattern
  * @author Denis Meyer
  * @website https://sites.google.com/site/calltopowersoftware/software
  * @version 1.0.0
  * @created 3/16/11
  * @file Logger.cpp
  *
  *  Copyright (C) 2014 Denis Meyer, calltopower88@googlemail.com
  *  This program is free software; you can redistribute it and/or modify
  *  it under the terms of the GNU General Public License as published by
  *  the Free Software Foundation; either version 2 of the License, or
  *  (at your option) any later version.
  *
  *  This program is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  *  GNU General Public License for more details.
  *
  *  You should have received a copy of the GNU General Public License along
  *  with this program; if not, write to the Free Software Foundation, Inc.,
  *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
  */
//#include "../include/Logger.h"

  // static variables
Logger* Logger::m_instance = 0;
std::string Logger::m_prefix = "";
std::string Logger::m_postfix = "";
std::string Logger::m_separator = " ";
bool Logger::m_output = true;
bool Logger::m_endl = true;
std::ostream* Logger::m_stream = &std::cout;
unsigned int Logger::m_nrLogs = 0;
std::string lastError = "";

/*************************************************
 * public
 *************************************************/

 // return the Logger instance
Logger* Logger::instance()
{
    if (!m_instance)
    {
        m_instance = new Logger;
    }

    return m_instance;
}

/*************************************************
 * helper
 *************************************************/

 // print nr newlines
void Logger::newLine(const int nr) const
{
    if (m_output)
    {
        for (int i = 0; i < abs(nr); ++i)
        {
            *m_stream << std::endl;
        }
    }
}

// prints str times times
void Logger::printTimes(const int times, const std::string str, const bool separator) const
{
    if (m_output && (abs(times) > 0))
    {
        *m_stream << m_prefix;
        for (int i = 0; i < abs(times); ++i)
        {
            if ((i != 0) && separator)
            {
                *m_stream << m_separator;
            }
            *m_stream << str;
        }
        *m_stream << m_postfix;
        if (m_endl)
        {
            *m_stream << std::endl;
        }
    }
}

/*************************************************
 * logging
 *************************************************/

 // log a std::string
bool Logger::log(const std::string str) const
{
    return logX("s", str.c_str());
}

// log an int
bool Logger::log(const int i) const
{
    return logX("i", i);
}

// log a double
bool Logger::log(const double d) const
{
    return logX("d", d);
}

// log a double**
bool Logger::log(double** d, const int rows, const int cols) const
{
    if (m_output && d)
    {
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                try {
                    *m_stream << d[i][j] << m_separator;
                }
                catch (...) {
                    return false;
                }
            }
            if (m_endl)
            {
                *m_stream << std::endl;
            }
        }
        ++m_nrLogs;
        return true;
    }
    return false;
}

// log a variable number of arguments
int Logger::logX(const std::string szTypes, ...) const
{
    int i = 0;
    if (m_output)
    {
        va_list vl;
        va_start(vl, szTypes);
        for (; szTypes[i] != '\0'; ++i)
        {
            if (i == 0)
            {
                *m_stream << m_prefix;
            }
            else
            {
                *m_stream << m_separator;
            }
            switch (szTypes[i])
            {
            case 'b':
                m_currType.i = va_arg(vl, int);
                *m_stream << ((m_currType.i == 0) ? "false" : "true");
                break;
            case 'i':
                m_currType.i = va_arg(vl, int);
                *m_stream << m_currType.i;
                break;
            case 'f':
            case 'd':
                m_currType.f = va_arg(vl, double);
                *m_stream << m_currType.f;
                break;
            case 'c':
                m_currType.c = va_arg(vl, int);
                *m_stream << m_currType.c;
                break;
            case 's':
                m_currType.s = va_arg(vl, char*);
                *m_stream << (m_currType.s != 0 ? std::string(m_currType.s) : "");
                break;
            default:
                break;
            }
        }
        if (i != 0)
        {
            *m_stream << m_postfix;
            if (m_endl)
            {
                *m_stream << std::endl;
            }
            ++m_nrLogs;
        }
    }
    return i;
}

/*************************************************
 * setter
 *************************************************/

 // set a prefix
void Logger::setPrefix(const std::string prefix)
{
    m_prefix = prefix;
}

// set a postfix
void Logger::setPostfix(const std::string postfix)
{
    m_postfix = postfix;
}

// set a separator
void Logger::setSeparator(const std::string separator)
{
    m_separator = separator;
}

// set flag if output to stream
void Logger::setOutput(const bool output)
{
    m_output = output;
}

// set flag if endline after each log
void Logger::setEndline(const bool endline)
{
    m_endl = endline;
}

// set if output to stream
void Logger::setStream(std::ostream& stream)
{
    if (m_stream && (m_stream != &std::cout))
    {
        delete(&m_stream);
    }
    m_stream = &stream;
}

/*************************************************
 * clearer/resetter
 *************************************************/

 // reset the number of successful logs
void Logger::resetNrOfLogs()
{
    m_nrLogs = 0;
}

// clear the prefix
void Logger::clearPrefix()
{
    m_prefix = "";
}

// clear the postfix
void Logger::clearPostfix()
{
    m_postfix = "";
}

// reset the separator
void Logger::resetSeparator()
{
    m_separator = " ";
}

/*************************************************
 * getter
 *************************************************/

 // return the successful number of logs
unsigned int Logger::getNrOfLogs() const
{
    return int(m_nrLogs);
}

// return the prefix
std::string Logger::getPrefix() const
{
    return std::string(m_prefix);
}

// return the postfix
std::string Logger::getPostfix() const
{
    return std::string(m_postfix);
}

// return the separator
std::string Logger::getSeparator() const
{
    return std::string(m_separator);
}

// return flag if output set
bool Logger::output() const
{
    return bool(m_output);
}

// return flag if endl after each log set
bool Logger::endl() const
{
    return bool(m_endl);
}

/*************************************************
 * private
 *************************************************/

 // ctor
Logger::Logger()
{
}

// dtor
Logger::~Logger()
{
    if (m_stream && (m_stream != &std::cout))
    {
        delete(&m_stream);
    }
}

// copy ctor
Logger::Logger(const Logger& l)
{
    // this cannot happen
}

// assignment operator
Logger& Logger::operator=(const Logger& l)
{
    // handle self assignment
    if (this == &l)
    {
        return *this;
    }
    // this cannot happen
    return *this;
}


#define VERSION "v1.0.0"

using std::string;

/**
 * main
 * test some of the Logger functionality
 */
int main(int argc, const char* argv[])
{
    Logger::instance()->newLine(2);
    Logger::instance()->log("Logger " + string(VERSION) + " by Denis Meyer");
    Logger::instance()->newLine(2);

    Logger::instance()->log("test suite");
    Logger::instance()->printTimes(50, "#");

    /* test case 0 */
    Logger::instance()->setOutput(true);
    Logger::instance()->newLine();
    Logger::instance()->log("0. logging normal strings");
    Logger::instance()->setPrefix("Log ----- ");
    Logger::instance()->setPostfix(" ----- /Log");
    Logger::instance()->log("string 1");
    Logger::instance()->clearPostfix();
    Logger::instance()->log("string 2");
    Logger::instance()->clearPrefix();
    Logger::instance()->setOutput(true);
    Logger::instance()->log("string 3");
    Logger::instance()->setOutput(false);
    Logger::instance()->log("string 4");
    Logger::instance()->setOutput(true);
    Logger::instance()->newLine();
    Logger::instance()->logX("si", "Successful number of logs: ", Logger::instance()->getNrOfLogs());
    Logger::instance()->newLine();

    /* test case 1 */
    Logger::instance()->newLine();
    Logger::instance()->log("1. logging variable number of arguments (w/o separator)");
    // without separator
    Logger::instance()->resetSeparator();
    Logger::instance()->setPrefix("Log ----- ");
    Logger::instance()->setPostfix(" ----- /Log");
    Logger::instance()->logX("fcsib", 3.41f, 'c', "string 1", 42, true);
    Logger::instance()->clearPostfix();
    Logger::instance()->logX("fcsib", 3.41f, 'c', "string 2", 42, false);
    Logger::instance()->clearPrefix();
    Logger::instance()->setOutput(true);
    Logger::instance()->logX("fcsib", 3.41f, 'c', "string 3", 42, true);
    Logger::instance()->setOutput(false);
    Logger::instance()->logX("fcsib", 3.41f, 'c', "string 4", 42, true);
    Logger::instance()->setOutput(true);
    Logger::instance()->newLine();
    Logger::instance()->logX("si", "Successful number of logs: ", Logger::instance()->getNrOfLogs());
    Logger::instance()->newLine();

    /* test case 2 */
    Logger::instance()->newLine();
    Logger::instance()->log("2. logging variable number of arguments (w separator)");
    // with separator
    Logger::instance()->setSeparator(" - ");
    Logger::instance()->setPrefix("Log ----- ");
    Logger::instance()->setPostfix(" ----- /Log");
    Logger::instance()->logX("fcsib", 3.41f, 'c', "string 1", 42, true);
    Logger::instance()->clearPostfix();
    Logger::instance()->logX("fcsib", 3.41f, 'c', "string 2", 42, false);
    Logger::instance()->clearPrefix();
    Logger::instance()->setOutput(true);
    Logger::instance()->logX("fcsib", 3.41f, 'c', "string 3", 42, true);
    Logger::instance()->setOutput(false);
    Logger::instance()->logX("fcsib", 3.41f, 'c', "string 4", 42, true);
    Logger::instance()->resetSeparator();
    Logger::instance()->setOutput(true);
    Logger::instance()->newLine();
    Logger::instance()->logX("si", "Successful number of logs: ", Logger::instance()->getNrOfLogs());
    Logger::instance()->newLine();

    /* test case 3 */
    Logger::instance()->newLine();
    Logger::instance()->log("3. logging an bool, an int and a double separately");
    Logger::instance()->setEndline(false);
    Logger::instance()->log("bool, int, double: ");
    Logger::instance()->logX("b", true);
    Logger::instance()->log(", ");
    Logger::instance()->log(42);
    Logger::instance()->log(", ");
    Logger::instance()->log(3.41);
    Logger::instance()->setEndline(true);
    Logger::instance()->newLine(2);
    Logger::instance()->logX("si", "Successful number of logs: ", Logger::instance()->getNrOfLogs());
    Logger::instance()->newLine();

    /* test case 4 */
    Logger::instance()->newLine();
    Logger::instance()->log("4. log return values");
    Logger::instance()->logX("si", "Number of arguments logged previously: ", Logger::instance()->log(42));
    Logger::instance()->logX("si", "Number of arguments logged previously: ", Logger::instance()->logX("ii", 42, 21));
    Logger::instance()->newLine();
    Logger::instance()->logX("si", "Successful number of logs: ", Logger::instance()->getNrOfLogs());
    Logger::instance()->newLine();

    /* test case 5 */
    Logger::instance()->newLine();
    Logger::instance()->log("5. helper");
    Logger::instance()->printTimes(10, "c");
    Logger::instance()->setSeparator(" - ");
    Logger::instance()->printTimes(10, "c", true);
    Logger::instance()->resetSeparator();
    Logger::instance()->newLine();
    Logger::instance()->logX("si", "Successful number of logs: ", Logger::instance()->getNrOfLogs());
    Logger::instance()->resetNrOfLogs();
    Logger::instance()->logX("si", "Successful number of logs after reset: ", Logger::instance()->getNrOfLogs());
    Logger::instance()->newLine();

    /* test case 6 */
    Logger::instance()->newLine();
    Logger::instance()->log("6. log double**");
    double** d;
    d = new double* [5];
    for (int i = 0; i < 5; ++i)
    {
        d[i] = new double[4];
    }
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            d[i][j] = i + j;
        }
    }
    Logger::instance()->setSeparator("\t");
    if (!Logger::instance()->log(d, 5, 4))
    {
        Logger::instance()->log("Error logging double**");
    }
    Logger::instance()->resetSeparator();
    for (int i = 0; i < 4; ++i)
    {
        delete d[i];
    }
    delete[] d;
    Logger::instance()->newLine();
    Logger::instance()->logX("si", "Successful number of logs: ", Logger::instance()->getNrOfLogs());
    Logger::instance()->newLine();

    Logger::instance()->printTimes(50, "#");
    Logger::instance()->log("/test suite");
    Logger::instance()->newLine(2);

    return 0;
}