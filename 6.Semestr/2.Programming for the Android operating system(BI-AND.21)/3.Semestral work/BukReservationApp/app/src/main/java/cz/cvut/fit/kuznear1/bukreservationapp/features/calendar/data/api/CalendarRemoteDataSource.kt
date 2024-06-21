package cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.data.api

import android.content.Context
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.domain.Calendar
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.domain.CreateDefaultCalendar

class CalendarRemoteDataSource(
    private val apiDescription: CalendarApiDescription,
) {

    suspend fun createCalendar(username: String, body: Calendar?): Calendar {
        return apiDescription.createCalendar(username, body)
    }

    suspend fun deleteCalendar(id: String, username: String): Calendar {
        return apiDescription.deleteCalendar(id, username)
    }

    suspend fun editCalendar(id: String, username: String, body: Calendar?): Calendar {
        return mapApiCalendar(apiDescription.editCalendar(id, username, body))
    }

    suspend fun getCalendar(id: String): Calendar {
        return mapApiCalendar(apiDescription.getCalendar(id))
    }

    suspend fun getCalendars(): List<Calendar> {
        val calendars = apiDescription.getCalendars().map { apiCalendar ->
            mapApiCalendar(apiCalendar)
        }

        return calendars
    }

    private fun mapApiCalendar(apiCalendar: ApiCalendar.Calendar): Calendar {
        return Calendar(
            calendar_id = apiCalendar.calendar_id,
            service_alias = apiCalendar.service_alias,
            reservation_type = apiCalendar.reservation_type,
            event_name = apiCalendar.event_name,
            max_people = apiCalendar.max_people,
            collision_with_itself = apiCalendar.collision_with_itself,
            collision_with_calendar = apiCalendar.collision_with_calendar,
            club_member_rules = apiCalendar.club_member_rules,
            active_member_rules = apiCalendar.active_member_rules,
            manager_rules = apiCalendar.manager_rules,
            mini_services = apiCalendar.mini_services,
        )
    }
}