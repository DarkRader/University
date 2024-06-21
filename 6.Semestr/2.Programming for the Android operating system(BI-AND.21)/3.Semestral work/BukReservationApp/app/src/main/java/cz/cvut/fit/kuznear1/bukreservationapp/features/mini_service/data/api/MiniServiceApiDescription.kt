package cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.data.api

import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.domain.Calendar
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.domain.MiniServiceRequest
import okhttp3.ResponseBody
import retrofit2.http.Body
import retrofit2.http.DELETE
import retrofit2.http.Field
import retrofit2.http.FormUrlEncoded
import retrofit2.http.GET
import retrofit2.http.POST
import retrofit2.http.PUT
import retrofit2.http.Path
import retrofit2.http.Query

interface MiniServiceApiDescription {

    @GET("mini_services")
    suspend fun getMiniServices(): List<ApiMiniService>

    @GET("mini_services/{id}")
    suspend fun getMiniService(@Path("id") id: String): ApiMiniService

    @POST("mini_services/create_mini_service")
    suspend fun createMiniService(
        @Query("username") username: String,
        @Body request: MiniServiceRequest?
    ): ApiMiniService

    @DELETE("mini_services/{mini_service_uuid}")
    suspend fun deleteMiniService(
        @Path("mini_service_uuid") miniServiceUuid: String,
        @Query("username") username: String
    ): ApiMiniService

    @PUT("mini_services/{mini_service_uuid}")
    suspend fun editMiniService(
        @Path("mini_service_uuid") miniServiceUuid: String,
        @Query("username") username: String,
        @Body request: MiniServiceRequest?
    ): ApiMiniService
}