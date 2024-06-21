package cz.cvut.fit.kuznear1.bukreservationapp.core.data.db

import android.content.Context
import androidx.room.Database
import androidx.room.Room
import androidx.room.RoomDatabase
import androidx.room.TypeConverters
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.data.db.CalendarDao
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.data.db.Converters
import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.data.db.DbCalendar
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.data.db.DbMiniService
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.data.db.MiniServiceDao
import cz.cvut.fit.kuznear1.bukreservationapp.features.profile.data.db.ProfileDao
import cz.cvut.fit.kuznear1.bukreservationapp.features.profile.data.db.DbUser
import cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.data.db.DbReservation
import cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.data.db.ReservationDao

@Database(version = 1, entities = [DbCalendar::class, DbMiniService::class, DbUser::class, DbReservation::class])
@TypeConverters(Converters::class)
abstract class BukReservationDatabase : RoomDatabase() {

    abstract fun calendarDao(): CalendarDao

    abstract fun miniServiceDao(): MiniServiceDao

    abstract fun profileDao(): ProfileDao

    abstract fun reservationDao(): ReservationDao

    companion object {

        fun newInstance(context: Context): BukReservationDatabase {
            return Room.databaseBuilder(context, BukReservationDatabase::class.java, "buk_res.db").build()
        }
    }
}