package cz.cvut.fit.kuznear1.bukreservationapp.features.profile.data.api

import okhttp3.ResponseBody
import retrofit2.Response
import retrofit2.http.GET
import retrofit2.http.Query

interface ProfileApiDescription {
    @GET("auth_is/login/callback")
    suspend fun authorized(
        @Query("code") code: String
    ) : Response<ResponseBody>
}