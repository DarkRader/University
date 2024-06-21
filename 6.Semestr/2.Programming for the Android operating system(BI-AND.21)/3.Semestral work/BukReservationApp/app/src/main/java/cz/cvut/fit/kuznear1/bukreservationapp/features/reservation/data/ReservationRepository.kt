package cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.data

import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.domain.MiniServiceResult
import cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.data.api.ReservationRemoteDataSource
import cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.data.db.ReservationLocalDataSource
import cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.domain.CreateEvent
import cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.domain.EventResult
import cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.domain.Reservation
import org.json.JSONObject

class ReservationRepository(
    private val localDataSource: ReservationLocalDataSource,
    private val remoteDataSource: ReservationRemoteDataSource
) {

    suspend fun postEvent(event: CreateEvent): EventResult {
        val response = remoteDataSource.postEvent(event)
        if(response.code() == 401) {
            return EventResult("", false)
        } else if(response.code() == 201) {
            return EventResult("", true)
        }
        val body = response.body()?.string()
        val message: String = if(body != null) {
            JSONObject(body).optString("message")
        } else {
            "No message!"
        }
        return EventResult(message, true)
    }

    suspend fun getAllReservations(): List<Reservation> {
        return localDataSource.getAllReservations()
    }

    suspend fun insertReservation(reservation: Reservation) {
        localDataSource.insert(reservation)
    }
}
