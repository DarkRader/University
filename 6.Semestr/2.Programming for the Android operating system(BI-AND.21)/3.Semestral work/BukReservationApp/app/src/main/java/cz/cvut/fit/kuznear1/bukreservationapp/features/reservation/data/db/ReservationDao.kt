package cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.data.db

import androidx.room.Dao
import androidx.room.Insert
import androidx.room.Query

@Dao
interface ReservationDao {
    @Query("SELECT * FROM reservation")
    suspend fun getAllReservations(): List<DbReservation>

    @Insert
    suspend fun insert(reservation: DbReservation)
}