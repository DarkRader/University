package cz.cvut.kuznear1.dogapp.features.fact.data.api

import cz.cvut.kuznear1.dogapp.features.fact.domain.Fact

class FactRemoteDataSource(private val apiDescription: FactApiDescription) {

    suspend fun getFacts(limit: Int): List<Fact> {
        return apiDescription.getFacts(limit).data.map { Fact(it.attributes.fact) }
    }
}