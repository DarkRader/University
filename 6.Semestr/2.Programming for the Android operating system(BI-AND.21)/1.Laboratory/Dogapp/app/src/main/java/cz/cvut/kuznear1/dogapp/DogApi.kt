package cz.cvut.kuznear1.dogapp

import com.jakewharton.retrofit2.converter.kotlinx.serialization.asConverterFactory
import kotlinx.serialization.ExperimentalSerializationApi
import kotlinx.serialization.SerialName
import kotlinx.serialization.Serializable
import kotlinx.serialization.json.Json
import okhttp3.MediaType.Companion.toMediaType
import okhttp3.OkHttpClient
import okhttp3.logging.HttpLoggingInterceptor
import retrofit2.Retrofit
import retrofit2.http.GET
import retrofit2.http.Query

interface DogApiDescription {

    @GET("facts")
    suspend fun getFacts(@Query("limit") limit: Int): DogFactsResponse
}

@Serializable
data class DogFactsResponse(val data: List<DogFactData>) {

    @Serializable
    data class DogFactData(val attributes: Attributes)

    @Serializable
    data class Attributes(@SerialName("body") val fact: String)
}

object DogDataSource {

    private val json = Json { ignoreUnknownKeys = true }

    @OptIn(ExperimentalSerializationApi::class)
    private val apiDescription: DogApiDescription = Retrofit.Builder()
        .baseUrl("https://dogapi.dog/api/v2/")
        .addConverterFactory(json.asConverterFactory("application/json".toMediaType()))
        .client(
            OkHttpClient.Builder()
                .addNetworkInterceptor(HttpLoggingInterceptor().setLevel(HttpLoggingInterceptor.Level.BODY))
                .build()
        )
        .build()
        .create(DogApiDescription::class.java)

    suspend fun getDogFacts(limit: Int): DogFactsResponse {
        return apiDescription.getFacts(limit)
    }
}