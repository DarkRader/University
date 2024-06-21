package cz.cvut.fit.kuznear1.firebase.features.notes.data

import com.google.firebase.firestore.FirebaseFirestore
import com.google.firebase.firestore.Query
import com.google.firebase.firestore.dataObjects
import cz.cvut.fit.kuznear1.firebase.features.notes.domain.Note
import kotlinx.coroutines.flow.Flow

class NotesRepository(
    private val firestore: FirebaseFirestore,
) {

    fun addNote(userId: String, note: Note) {
        firestore.collection("users")
            .document(userId)
            .collection("notes")
            .add(note)
    }

    fun getNotesStream(userId: String): Flow<List<Note>> {
        return firestore.collection("users")
            .document(userId)
            .collection("notes")
            .whereGreaterThan("timestamp", 0)
            .orderBy("timestamp", Query.Direction.DESCENDING)
            .dataObjects()
    }
}
