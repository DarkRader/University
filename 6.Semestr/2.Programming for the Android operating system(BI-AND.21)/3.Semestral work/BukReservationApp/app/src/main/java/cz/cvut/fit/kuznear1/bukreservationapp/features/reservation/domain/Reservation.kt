package cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.domain

data class Reservation(
    val reservationFrom: String,
    val reservationTo: String,
    val typeReservation: String
)