package cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.data.api

import cz.cvut.fit.kuznear1.bukreservationapp.features.calendar.domain.Calendar
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.data.api.ApiMiniService
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.domain.MiniServiceRequest
import okhttp3.ResponseBody
import retrofit2.http.Body
import retrofit2.http.DELETE
import retrofit2.http.GET
import retrofit2.http.POST
import retrofit2.http.PUT
import retrofit2.http.Path
import retrofit2.http.Query

interface CalendarApiDescription {

    @GET("calendars")
    suspend fun getJsonCalendars(): ResponseBody

    @GET("calendars")
    suspend fun getCalendars(): List<ApiCalendar.Calendar>

    @GET("calendar/{id}")
    suspend fun getCalendar(@Path("id") id: String): ApiCalendar.Calendar

    @POST("calendars/create_calendar")
    suspend fun createCalendar(
        @Query("username") username: String,
        @Body request: Calendar?
    ): Calendar

    @DELETE("calendars/{calendar_id}")
    suspend fun deleteCalendar(
        @Path("calendar_id") calendarId: String,
        @Query("username") username: String
    ): Calendar

    @PUT("calendars/{calendar_id}")
    suspend fun editCalendar(
        @Path("calendar_id") calendarId: String,
        @Query("username") username: String,
        @Body request: Calendar?
    ): ApiCalendar.Calendar
}