package cz.cvut.kuznear1.dogapp.features.fact.data

import cz.cvut.kuznear1.dogapp.features.fact.data.api.FactRemoteDataSource

class FactRepository(private val remoteDataSource: FactRemoteDataSource) {

    suspend fun getFacts(limit: Int) = remoteDataSource.getFacts(limit)
}