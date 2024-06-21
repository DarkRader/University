package cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.data.api

import cz.cvut.fit.kuznear1.bukreservationapp.features.reservation.domain.CreateEvent
import okhttp3.ResponseBody
import retrofit2.Response
import retrofit2.http.Body
import retrofit2.http.POST

interface ReservationApiDescription {
    @POST("events/post")
    suspend fun postEvent(
        @Body request: CreateEvent
    ) : Response<ResponseBody>
}