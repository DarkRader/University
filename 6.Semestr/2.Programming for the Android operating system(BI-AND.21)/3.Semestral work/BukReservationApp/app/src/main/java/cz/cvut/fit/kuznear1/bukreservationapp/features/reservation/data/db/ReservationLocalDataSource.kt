package cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.data.db

import cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.domain.Reservation

class ReservationLocalDataSource(
    private val reservationDao: ReservationDao
) {

    private fun DbReservation.toDomain(): Reservation {
        return Reservation(
            typeReservation = typeReservation,
            reservationFrom = reservationFrom,
            reservationTo = reservationTo
        )
    }

    suspend fun getAllReservations(): List<Reservation> {
        val dbReservations = reservationDao.getAllReservations()
        return dbReservations.map { it.toDomain() }
    }

    suspend fun insert(reservation: Reservation) {
        val dbReservation = DbReservation(
            typeReservation = reservation.typeReservation,
            reservationFrom = reservation.reservationFrom,
            reservationTo = reservation.reservationTo
        )
        reservationDao.insert(dbReservation)
    }
}