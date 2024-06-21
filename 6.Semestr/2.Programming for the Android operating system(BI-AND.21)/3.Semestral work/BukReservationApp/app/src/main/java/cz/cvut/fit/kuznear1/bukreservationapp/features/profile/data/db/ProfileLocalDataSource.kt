package cz.cvut.fit.kuznear1.bukreservationapp.features.profile.data.db

import cz.cvut.fit.kuznear1.bukreservationapp.features.profile.domain.User
import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.map

class ProfileLocalDataSource(private val profileDao: ProfileDao) {
    private fun DbUser.toDomain(): User {
        return User(
            username = username
        )
    }

    suspend fun getAllUsers(): List<User> {
        val dbUser = profileDao.getAllUsers()
        return dbUser.map { it.toDomain() }
    }

    suspend fun getUser(id: String): User? = profileDao.getUser(id)?.toDomain()

    suspend fun insert(username: String) {
        val dbUser = DbUser(
            username = username
        )
        profileDao.insert(dbUser)
    }

    suspend fun deleteAll() {
        profileDao.deleteAll()
    }
}