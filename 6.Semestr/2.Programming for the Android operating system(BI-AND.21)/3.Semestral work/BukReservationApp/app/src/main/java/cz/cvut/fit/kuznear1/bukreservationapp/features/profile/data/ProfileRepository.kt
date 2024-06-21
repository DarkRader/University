package cz.cvut.fit.kuznear1.bukreservationapp.features.profile.data

import cz.cvut.fit.kuznear1.bukreservationapp.features.profile.data.api.ProfileRemoteDataSource
import cz.cvut.fit.kuznear1.bukreservationapp.features.profile.data.db.ProfileLocalDataSource

class ProfileRepository(
    private val localDataSource: ProfileLocalDataSource,
    private val remoteDataSource: ProfileRemoteDataSource
) {
    suspend fun authorized(code: String): String? {
        val username = remoteDataSource.authorized(code)
        localDataSource.deleteAll()
        if(username != null) {
            localDataSource.insert(username)
            return username
        }
        return null
    }

    suspend fun getUser(): String? {
        val users = localDataSource.getAllUsers()
        if(users.isEmpty()) {
            return null
        }
        return users.first().username
    }
}