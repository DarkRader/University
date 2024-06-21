package cz.cvut.kuznear1.dogapp.features.fact.data.api

import retrofit2.http.GET
import retrofit2.http.Query

interface FactApiDescription {

    @GET("facts")
    suspend fun getFacts(@Query("limit") limit: Int): FactsResponse
}