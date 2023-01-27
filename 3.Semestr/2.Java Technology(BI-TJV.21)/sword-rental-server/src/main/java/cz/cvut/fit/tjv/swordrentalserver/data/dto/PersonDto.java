package cz.cvut.fit.tjv.swordrentalserver.data.dto;

import java.io.Serializable;
import java.util.HashSet;
import java.util.Set;

public class PersonDto implements Serializable {
    private long personId;
    private Set<Long> wantedSwordAlert = new HashSet<>();
    private String username;
    private String name;
    private String surname;
    private long phoneNumber;
    private String email;
    private Set<Long> wishList = new HashSet<>();

    public long getPersonId() {
        return personId;
    }

    public void setPersonId(long personId) {
        this.personId = personId;
    }

    public Set<Long> getWantedSwordAlert() {
        return wantedSwordAlert;
    }

    public void setWantedSwordAlert(Set<Long> wantedSwordAlert) {
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

    public Set<Long> getWishList() {
        return wishList;
    }

    public void setWishList(Set<Long> wishList) {
        this.wishList = wishList;
    }
}
