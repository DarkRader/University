package cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.data.db

import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.domain.Calendar
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.map


class CalendarLocalDataSource(private val calendarDao: CalendarDao) {

    fun getCalendarStream(): Flow<List<Calendar>> = calendarDao.getCalendarStream().map { dbCalendar ->
        dbCalendar.map { it.toDomain() }
    }

    private fun DbCalendar.toDomain(): Calendar {
        return Calendar(
            calendar_id = calendar_id,
            service_alias = service_alias,
            reservation_type = reservation_type,
            event_name = event_name,
            max_people = max_people,
            collision_with_itself = collision_with_itself,
            collision_with_calendar = collision_with_calendar,
            club_member_rules = club_member_rules,
            active_member_rules = active_member_rules,
            manager_rules = manager_rules,
            mini_services = mini_services,
        )
    }

    suspend fun getAllCalendars(): List<Calendar> {
        val dbCalendars = calendarDao.getAllCalendars()
        return dbCalendars.map { it.toDomain() }
    }

    suspend fun getCalendar(id: String): Calendar? = calendarDao.getCalendar(id)?.toDomain()

    suspend fun insertAll(calendars: List<Calendar>) {
        val dbCalendar = calendars.map { calendar ->
            DbCalendar(
                calendar_id = calendar.calendar_id,
                service_alias = calendar.service_alias,
                reservation_type = calendar.reservation_type,
                event_name = calendar.event_name,
                max_people = calendar.max_people,
                collision_with_itself = calendar.collision_with_itself,
                collision_with_calendar = calendar.collision_with_calendar,
                club_member_rules = calendar.club_member_rules,
                active_member_rules = calendar.active_member_rules,
                manager_rules = calendar.manager_rules,
                mini_services = calendar.mini_services,
            )
        }
        calendarDao.insertAll(dbCalendar)
    }

    suspend fun insert(calendar: Calendar) {
        val dbCalendar = DbCalendar(
            calendar_id = calendar.calendar_id,
            service_alias = calendar.service_alias,
            reservation_type = calendar.reservation_type,
            event_name = calendar.event_name,
            max_people = calendar.max_people,
            collision_with_itself = calendar.collision_with_itself,
            collision_with_calendar = calendar.collision_with_calendar,
            club_member_rules = calendar.club_member_rules,
            active_member_rules = calendar.active_member_rules,
            manager_rules = calendar.manager_rules,
            mini_services = calendar.mini_services,
        )
        calendarDao.insert(dbCalendar)
    }

    suspend fun deleteCalendarById(id: String) {
        calendarDao.deleteCalendarById(id)
    }

    suspend fun deleteAll() {
        calendarDao.deleteAll()
    }
}
