package cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.data.db

import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity(tableName = "reservation")
data class DbReservation(
    @PrimaryKey(autoGenerate = true)
    val id: Long = 0,
    val typeReservation: String,
    val reservationFrom: String,
    val reservationTo: String,
)