package cz.cvut.fit.tjv.swordrentalclient.model.dto;

import org.hibernate.validator.constraints.Range;

import javax.validation.constraints.NotEmpty;
import java.util.HashSet;
import java.util.Set;

public class PersonDto {
    private long personId;

    //Contains only recently freed swords
    private Set<Long> wantedSwordAlert = new HashSet<>();
    @NotEmpty(message = "Username shouldn't be empty")
    private String username;
    @NotEmpty(message = "Name shouldn't be empty")
    private String name;
    @NotEmpty(message = "Surname shouldn't be empty")
    private String surname;
    @Range(min = 10000, message = "Invalid phone number")
    private long phoneNumber;
    @NotEmpty(message = "Email shouldn't be empty")
    private String email;

    private Set<Long> wishList = new HashSet<>();

    public PersonDto(long personId, Set<Long> wantedSwordAlert, String username, String name, String surname, long phoneNumber, String email, Set<Long> wishList) {
        this.personId = personId;
        this.wantedSwordAlert = wantedSwordAlert;
        this.username = username;
        this.name = name;
        this.surname = surname;
        this.phoneNumber = phoneNumber;
        this.email = email;
        this.wishList = wishList;
    }

    public PersonDto() {}

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
