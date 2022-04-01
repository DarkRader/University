#include <string>
#include <iostream>
#include <cassert>

struct SStudent
{
    std::string m_name;
    int m_knowledge_level;
};

class CTeacher
{
    public:
        CTeacher ( const std::string & name )
        :m_name(name),
         m_passed_students(0)
        {}
        // ====================================================
        size_t passed_students ( void ) const
        {
            return m_passed_students;
        }
        // ====================================================
        void passed_students ( size_t newly_passed )
        {
            m_passed_students += newly_passed;
        }
        // ====================================================
    private:
        std::string m_name;
        size_t m_passed_students;
};

class CList
{
    public:
        // ====================================================
        // Kopirovani se bude resit na dalsich cvicenich,
        // tentokrat si ho tedy odpustime.
        // ====================================================
        CList              ( const CList & ) = delete;
        CList & operator = ( const CList & ) = delete;
        CList              ( CList && )      = delete;
        CList & operator = ( CList && )      = delete;
        // ====================================================
        CList ( void );
        // ====================================================
        ~CList ( void );
        // ====================================================
        CList & add_student ( const SStudent & student );
        // ====================================================
        const SStudent & get_student ( size_t idx ) const;
        // ====================================================
        size_t size ( void ) const;
        // ====================================================
        const SStudent * begin ( void ) const;
        // ====================================================
        const SStudent * end ( void ) const;
        // ====================================================
    private:
        // todo
};

class CExam
{
    public:
        CExam ( CTeacher & teacher, int difficulty_level );
        // =============================================================
        void start_exam ( const CList & student_list ) const;
        // =============================================================
    private:
        // todo
};

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
    return 0;
}
