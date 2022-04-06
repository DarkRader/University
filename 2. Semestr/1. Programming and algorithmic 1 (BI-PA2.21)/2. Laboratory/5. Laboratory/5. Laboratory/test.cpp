#include <cassert>

#include "SStudent.hpp"
#include "CList.hpp"
#include "CTeacher.hpp"
#include "CExam.hpp"

int main ( void )
{
    CTeacher honza("Honza"), franta("Franta");
    assert( honza.passed_students() == 0 );

    CList student_list1;
    student_list1.add_student({"Tomas", 5}).add_student({"Patrik", 24}).add_student({"Pepa", 25}).add_student({"Jirka", 88});

    CExam exam1(honza, 25);
    exam1.start_exam(student_list1);
    assert( honza.passed_students() == 2 );

    exam1.start_exam(student_list1);
    assert( honza.passed_students() == 4 );

    CExam exam2(honza, 50);
    exam2.start_exam(student_list1);
    assert( honza.passed_students() == 5 );

    CList student_list2;
    CExam exam3(franta, 0);
    exam3.start_exam(student_list2);
    assert( franta.passed_students() == 0 );

    exam3.start_exam(student_list1);
    assert( franta.passed_students() == 4 );

    student_list2.add_student({"Franta", 99});

    CExam exam4(honza, 100), exam5(franta, 99);
    exam4.start_exam(student_list2);
    assert ( honza.passed_students() == 5 );

    exam5.start_exam(student_list2);
    assert ( franta.passed_students() == 5 );

    exam3.start_exam(student_list1);
    assert ( franta.passed_students() == 9 );

    //CList student_list3 = student_list1; // volá se operator =, nebo kopírující konstruktor?
    //exam3.start_exam(student_list3);
    //assert ( franta.passed_students() == 13 );

    //student_list3 = student_list2;
    //exam3.start_exam(student_list3);
    //assert ( franta.passed_students() == 14 );

    //student_list3 = student_list3;
    //exam3.start_exam(student_list3);
    //assert ( franta.passed_students() == 15 );

    //CList student_list4 = std::move(student_list1);
    //exam3.start_exam(student_list4);
    //assert ( franta.passed_students() == 19 );

    //student_list3 = std::move(student_list2);
    //exam3.start_exam(student_list4);
    //assert ( franta.passed_students() == 20 );

    return 0;
}
