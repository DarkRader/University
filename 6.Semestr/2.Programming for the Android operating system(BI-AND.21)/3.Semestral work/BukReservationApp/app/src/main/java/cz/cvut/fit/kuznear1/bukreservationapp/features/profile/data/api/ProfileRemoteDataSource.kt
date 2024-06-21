package cz.cvut.fit.kuznear1.bukreservationapp.features.profile.data.api

import android.util.Log
import retrofit2.HttpException
import retrofit2.Response

class ProfileRemoteDataSource(
    private val apiDescription: ProfileApiDescription,
) {

    suspend fun authorized(code: String): String? {
        val response = apiDescription.authorized(code)
        val url = response.raw().request.url.toString()
        val regex = "username=([^&]+)".toRegex()
        return regex.find(url)?.groups?.get(1)?.value
    }
}