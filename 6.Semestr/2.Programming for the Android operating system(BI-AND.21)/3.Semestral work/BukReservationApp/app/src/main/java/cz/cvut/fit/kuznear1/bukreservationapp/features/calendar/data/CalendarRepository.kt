package cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.data

import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.data.api.CalendarRemoteDataSource
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.data.db.CalendarLocalDataSource
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.domain.Calendar
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.domain.CalendarResult
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.domain.CalendarsResult
import kotlinx.coroutines.flow.first

import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.withContext
import okhttp3.ResponseBody

class CalendarRepository (
    private val localDataSource: CalendarLocalDataSource,
    private val remoteDataSource: CalendarRemoteDataSource,
) {

    suspend fun createCalendar(username: String, body: Calendar?): CalendarResult {
        return try{
            val creatingCalendar = remoteDataSource.createCalendar(username, body)
            localDataSource.insert(creatingCalendar)
            CalendarResult(creatingCalendar, isSuccess = true)
        } catch (t: Throwable) {
            CalendarResult(null, isSuccess = false)
        }
    }

    suspend fun deleteCalendar(id: String, username: String): CalendarResult {
        return try{
            val deletedCalendar = remoteDataSource.deleteCalendar(id, username)
            localDataSource.deleteCalendarById(deletedCalendar.calendar_id)
            CalendarResult(deletedCalendar, isSuccess = true)
        } catch (t: Throwable) {
            CalendarResult(null, isSuccess = false)
        }
    }

    suspend fun editCalendar(id: String, username: String, body: Calendar?): CalendarResult {
        return try{
            val editedCalendar = remoteDataSource.editCalendar(id, username, body)
            localDataSource.deleteCalendarById(editedCalendar.calendar_id)
            localDataSource.insert(editedCalendar)
            CalendarResult(editedCalendar, isSuccess = true)
        } catch (t: Throwable) {
            CalendarResult(null, isSuccess = false)
        }
    }

    suspend fun getCalendars(): CalendarsResult {
        return try {
            val calendars = remoteDataSource.getCalendars()
            localDataSource.deleteAll()
            localDataSource.insertAll(calendars)
            CalendarsResult(calendars, isSuccess = true)
        } catch (t: Throwable) {
            CalendarsResult(localDataSource.getCalendarStream().first(), isSuccess = false)
        }
    }

    suspend fun getAllCalendar() = localDataSource.getAllCalendars()

    suspend fun getCalendar(id: String) = localDataSource.getCalendar(id)
}