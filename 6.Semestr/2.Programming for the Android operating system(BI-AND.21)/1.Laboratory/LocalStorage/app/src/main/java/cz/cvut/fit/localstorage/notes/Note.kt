package cz.cvut.fit.localstorage.notes

import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity(tableName = "note_db")
data class Note(
    @PrimaryKey(autoGenerate = true)
    val id: Long = 0,
    @ColumnInfo("note_text")
    val text: String,
    val title: String = "",
    @ColumnInfo(defaultValue = "")
    val subtitle: String = "",
)
