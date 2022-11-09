#pragma once

#include <string>

class CTeacher
{
public:
    CTeacher ( const std::string & name );
    size_t passed_students ( void ) const;
    void passed_students ( size_t newly_passed );
private:
    std::string m_name;
    size_t m_passed_students;
};
