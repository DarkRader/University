package cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.data.api

import cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.domain.CreateEvent
import okhttp3.ResponseBody
import retrofit2.Response

class ReservationRemoteDataSource(
    private val apiDescription: ReservationApiDescription
) {
    suspend fun postEvent(event: CreateEvent): Response<ResponseBody> {
        return apiDescription.postEvent(event)
    }
}