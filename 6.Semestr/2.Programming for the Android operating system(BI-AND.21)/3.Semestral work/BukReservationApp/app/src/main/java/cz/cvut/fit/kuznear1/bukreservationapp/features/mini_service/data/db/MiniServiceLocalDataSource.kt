package cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.data.db

import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.domain.MiniService
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.map

class MiniServiceLocalDataSource(private val miniServiceDao: MiniServiceDao) {

    fun getMiniServicesStream(): Flow<List<MiniService>> = miniServiceDao.getMiniServicesStream().map { dbMiniServices ->
        dbMiniServices.map { it.toDomain() }
    }

    private fun DbMiniService.toDomain(): MiniService {
        return MiniService(
            uuid = uuid,
            name = name,
            service_alias = service_alias
        )
    }

    suspend fun getAllMiniServices(): List<MiniService> {
        val dbMiniServices = miniServiceDao.getAllMiniServices()
        return dbMiniServices.map { it.toDomain() }
    }

    suspend fun getMiniService(id: String): MiniService? = miniServiceDao.getMiniService(id)?.toDomain()

    suspend fun insertAll(miniServices: List<MiniService>) {
        val dbMiniService = miniServices.map { miniService ->
            DbMiniService(
                uuid = miniService.uuid,
                name = miniService.name,
                service_alias = miniService.service_alias
            )
        }
        miniServiceDao.insertAll(dbMiniService)
    }

    suspend fun insert(miniService: MiniService) {
        val dbMiniService = DbMiniService(
            uuid = miniService.uuid,
            name = miniService.name,
            service_alias = miniService.service_alias
        )
        miniServiceDao.insert(dbMiniService)
    }

    suspend fun deleteMiniServiceById(id: String) {
        miniServiceDao.deleteMiniServiceById(id)
    }

    suspend fun deleteAll() {
        miniServiceDao.deleteAll()
    }
}