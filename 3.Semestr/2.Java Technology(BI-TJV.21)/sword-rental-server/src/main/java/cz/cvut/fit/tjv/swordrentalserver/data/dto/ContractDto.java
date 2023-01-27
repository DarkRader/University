package cz.cvut.fit.tjv.swordrentalserver.data.dto;

public class ContractDto {
    private long contractId;
    private String date;
    private long price;
    private String event;
    private String deliveryService;
    private Long person;
    private Long sword;

    public long getContractId() {
        return contractId;
    }

    public void setContractId(long contractId) {
        this.contractId = contractId;
    }

    public String getDate() {
        return date;
    }

    public void setDate(String date) {
        this.date = date;
    }

    public long getPrice() {
        return price;
    }

    public void setPrice(long price) {
        this.price = price;
    }

    public String getEvent() {
        return event;
    }

    public String getDeliveryService() {
        return deliveryService;
    }

    public void setDeliveryService(String deliveryService) {
        this.deliveryService = deliveryService;
    }

    public void setEvent(String event) {
        this.event = event;
    }

    public Long getPerson() {
        return person;
    }

    public void setPerson(Long person) {
        this.person = person;
    }

    public Long getSword() {
        return sword;
    }

    public void setSword(Long sword) {
        this.sword = sword;
    }
}
