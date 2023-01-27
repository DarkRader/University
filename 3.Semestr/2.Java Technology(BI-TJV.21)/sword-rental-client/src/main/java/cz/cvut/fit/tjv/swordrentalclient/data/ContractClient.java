package cz.cvut.fit.tjv.swordrentalclient.data;

import cz.cvut.fit.tjv.swordrentalclient.model.dto.ContractDto;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.web.client.RestTemplateBuilder;
import org.springframework.stereotype.Component;
import org.springframework.web.client.RestTemplate;

import java.util.Arrays;
import java.util.List;

@Component
public class ContractClient {
    private static final String ONE_URI = "/{id}";
    private static final String ROOT_RESOURCE_URL = "http://localhost:8080/contracts";

    private final RestTemplate restTemplate;

    @Autowired
    public ContractClient(RestTemplateBuilder restTemplateBuilder) {
        restTemplate = restTemplateBuilder.rootUri(ROOT_RESOURCE_URL).build();
    }

    public ContractDto create(ContractDto contractDto) {
        restTemplate.postForLocation("/", contractDto);
        return contractDto;
    }

    public ContractDto readById(Long id) {
        return restTemplate.getForObject(ONE_URI, ContractDto.class, id);
    }

    public List<ContractDto> readAll() {
        ContractDto[] response = restTemplate.getForObject("/", ContractDto[].class);
        if (response != null) {
            return Arrays.asList(response);
        }
        return null;
    }

    public void update(ContractDto swordDto, Long id) {
        restTemplate.put("/" + id, swordDto);
    }


    public void delete(Long id) {
        restTemplate.delete("/" + id);
    }
}
