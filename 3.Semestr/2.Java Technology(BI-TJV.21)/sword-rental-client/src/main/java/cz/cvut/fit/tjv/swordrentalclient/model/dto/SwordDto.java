package cz.cvut.fit.tjv.swordrentalclient.model.dto;

import org.hibernate.validator.constraints.Range;

import javax.validation.constraints.NotEmpty;
import java.util.HashSet;
import java.util.Set;

public class SwordDto {
    private long swordId;
    @NotEmpty(message = "Type to shouldn't be empty")
    private String type;
    @Range(min = 1, message = "The price cannot be zero")
    private long price;
    private long weight;
    private long length;

    private Set<Long> peopleWhoWishesForThisSword = new HashSet<>();

    public SwordDto(long swordId, String type, long price, long weight, long length, Set<Long> peopleWhoWishesForThisSword) {
        this.swordId = swordId;
        this.type = type;
        this.price = price;
        this.weight = weight;
        this.length = length;
        this.peopleWhoWishesForThisSword = peopleWhoWishesForThisSword;
    }

    public SwordDto() {}

    public long getSwordId() {
        return swordId;
    }

    public void setSwordId(long swordId) {
        this.swordId = swordId;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public long getPrice() {
        return price;
    }

    public void setPrice(long price) {
        this.price = price;
    }

    public long getWeight() {
        return weight;
    }

    public void setWeight(long weight) {
        this.weight = weight;
    }

    public long getLength() {
        return length;
    }

    public void setLength(long length) {
        this.length = length;
    }

    public Set<Long> getPeopleWhoWishesForThisSword() {
        return peopleWhoWishesForThisSword;
    }

    public void setPeopleWhoWishesForThisSword(Set<Long> peopleWhoWishesForThisSword) {
        this.peopleWhoWishesForThisSword = peopleWhoWishesForThisSword;
    }
}
