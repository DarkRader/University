package cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.data.api

import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.domain.MiniService
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.domain.MiniServiceRequest

class MiniServiceRemoteDataSource(
    private val apiDescription: MiniServiceApiDescription
) {

    suspend fun createMiniService(username: String, body: MiniServiceRequest?): MiniService {
        return mapApiMiniService(apiDescription.createMiniService(username, body))
    }

    suspend fun deleteMiniService(id: String, username: String): MiniService {
        return mapApiMiniService(apiDescription.deleteMiniService(id, username))
    }

    suspend fun editMiniService(
        id: String,
        username: String,
        body: MiniServiceRequest?
    ): MiniService {
        return mapApiMiniService(apiDescription.editMiniService(id, username, body))
    }

    suspend fun getMiniServices(): List<MiniService> {
        val miniServices = apiDescription.getMiniServices().map { apiMiniService ->
            mapApiMiniService(apiMiniService)
        }

        return miniServices
    }

    suspend fun getMiniService(id: String): MiniService {
        return mapApiMiniService(apiDescription.getMiniService(id))
    }

    private fun mapApiMiniService(apiMiniService: ApiMiniService): MiniService {
        return MiniService(
            uuid = apiMiniService.uuid,
            name = apiMiniService.name,
            service_alias = apiMiniService.service_alias
        )
    }
}