package cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.data.db

import androidx.room.Dao
import androidx.room.Insert
import androidx.room.Query
import kotlinx.coroutines.flow.Flow

@Dao
interface CalendarDao {

    @Query("SELECT * FROM calendar")
    fun getCalendarStream(): Flow<List<DbCalendar>>

    @Query("SELECT * FROM calendar")
    suspend fun getAllCalendars(): List<DbCalendar>

    @Query("SELECT * FROM calendar WHERE calendar_id = :id")
    suspend fun getCalendar(id: String): DbCalendar?

    @Insert
    suspend fun insertAll(calendars: List<DbCalendar>)

    @Insert
    suspend fun insert(calendar: DbCalendar)

    @Query("DELETE FROM calendar WHERE calendar_id = :id")
    suspend fun deleteCalendarById(id: String)

    @Query("DELETE FROM calendar")
    suspend fun deleteAll()

}