package cz.cvut.fit.tjv.swordrentalserver.data.entity;

import javax.persistence.*;
import java.io.Serializable;
import java.util.HashSet;
import java.util.Set;

@Entity
@Table(name = "person")
public class Person implements Serializable {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private long personId;

    //Contains only recently freed swords
    @ManyToMany
    private Set<Sword> wantedSwordAlert = new HashSet<>();
    private String username;
    private String name;
    private String surname;
    private long phoneNumber;
    private String email;

    @ManyToMany
    private Set<Sword> wishList = new HashSet<>();

    public Person(long personId, Set<Sword> wantedSwordAlert, String username, String name, String surname, long phoneNumber, String email, Set<Sword> wishList) {
        this.personId = personId;
        this.wantedSwordAlert = wantedSwordAlert;
        this.username = username;
        this.name = name;
        this.surname = surname;
        this.phoneNumber = phoneNumber;
        this.email = email;
        this.wishList = wishList;
    }

    public Person() {}

    public long getPersonId() {
        return personId;
    }

    public void setPersonId(long personId) {
        this.personId = personId;
    }

    public Set<Sword> getWantedSwordAlert() {
        return wantedSwordAlert;
    }

    public void setWantedSwordAlert(Set<Sword> wantedSwordAlert) {
        this.wantedSwordAlert = wantedSwordAlert;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getSurname() {
        return surname;
    }

    public void setSurname(String surname) {
        this.surname = surname;
    }

    public long getPhoneNumber() {
        return phoneNumber;
    }

    public void setPhoneNumber(long phoneNumber) {
        this.phoneNumber = phoneNumber;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public Set<Sword> getWishList() {
        return wishList;
    }

    public void setWishList(Set<Sword> wishList) {
        this.wishList = wishList;
    }

    //For tests

//    @Override
//    public boolean equals(Object o) {
//        if (this == o) return true;
//        if (o == null || getClass() != o.getClass()) return false;
//        Person person = (Person) o;
//        return personId == person.personId && phoneNumber == person.phoneNumber && Objects.equals(wantedSwordAlert, person.wantedSwordAlert) && Objects.equals(username, person.username) && Objects.equals(name, person.name) && Objects.equals(surname, person.surname) && Objects.equals(email, person.email) && Objects.equals(wishList, person.wishList);
//    }
//
//    @Override
//    public int hashCode() {
//        return Objects.hash(personId, wantedSwordAlert, username, name, surname, phoneNumber, email, wishList);
//    }
//
//    @Override
//    public String toString() {
//        return "Person{" +
//                "personId=" + personId +
//                ", wantedSwordAlert=" + wantedSwordAlert +
//                ", username='" + username + '\'' +
//                ", name='" + name + '\'' +
//                ", surname='" + surname + '\'' +
//                ", phoneNumber=" + phoneNumber +
//                ", email='" + email + '\'' +
//                ", wishList=" + wishList +
//                '}';
//    }
}
