package cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.data

import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.data.api.MiniServiceRemoteDataSource
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.data.db.MiniServiceLocalDataSource
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.domain.MiniServiceRequest
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.domain.MiniServiceResult
import cz.cvut.fit.kuznear1.bukreservationapp.features.mini_service.domain.MiniServicesResult
import kotlinx.coroutines.flow.first

class MiniServiceRepository(
    private val localDataSource: MiniServiceLocalDataSource,
    private val remoteDataSource: MiniServiceRemoteDataSource
) {

    suspend fun createMiniService(username: String, body: MiniServiceRequest?): MiniServiceResult {
        return try {
            val creatingMiniService = remoteDataSource.createMiniService(username, body)
            localDataSource.insert(creatingMiniService)
            MiniServiceResult(creatingMiniService, isSuccess = true)
        } catch (t: Throwable) {
            MiniServiceResult(null, isSuccess = false)
        }
    }

    suspend fun deleteMiniService(id: String, username: String): MiniServiceResult {
        return try {
            val deletedMiniService = remoteDataSource.deleteMiniService(id, username)
            localDataSource.deleteMiniServiceById(deletedMiniService.uuid)
            MiniServiceResult(deletedMiniService, isSuccess = true)
        } catch (t: Throwable) {
            MiniServiceResult(null, isSuccess = false)
        }
    }

    suspend fun editMiniService(
        id: String,
        username: String,
        body: MiniServiceRequest?
    ) : MiniServiceResult {
        return try {
            val editedMiniService = remoteDataSource.editMiniService(id, username, body)
            localDataSource.deleteMiniServiceById(editedMiniService.uuid)
            localDataSource.insert(editedMiniService)
            MiniServiceResult(editedMiniService, true)
        } catch (t: Throwable) {
            MiniServiceResult(null, false)
        }
    }

    suspend fun getMiniServices(): MiniServicesResult {
        return try {
            val miniServices = remoteDataSource.getMiniServices()
            localDataSource.deleteAll()
            localDataSource.insertAll(miniServices)
            MiniServicesResult(miniServices, isSuccess = true)
        } catch (t: Throwable) {
            MiniServicesResult(localDataSource.getMiniServicesStream().first(), isSuccess = false)
        }
    }

    suspend fun getAllMiniServices() = localDataSource.getAllMiniServices()

    suspend fun getMiniService(id: String) = localDataSource.getMiniService(id)
}