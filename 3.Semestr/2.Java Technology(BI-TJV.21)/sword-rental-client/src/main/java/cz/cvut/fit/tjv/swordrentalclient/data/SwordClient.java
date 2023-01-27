package cz.cvut.fit.tjv.swordrentalclient.data;

import cz.cvut.fit.tjv.swordrentalclient.model.dto.SwordDto;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.web.client.RestTemplateBuilder;
import org.springframework.stereotype.Component;
import org.springframework.web.client.RestTemplate;

import java.util.Arrays;
import java.util.List;

@Component
public class SwordClient {
    private static final String ONE_URI = "/{id}";
    private static final String ROOT_RESOURCE_URL = "http://localhost:8080/swords";

    private final RestTemplate restTemplate;

    @Autowired
    public SwordClient(RestTemplateBuilder restTemplateBuilder) {
        restTemplate = restTemplateBuilder.rootUri(ROOT_RESOURCE_URL).build();
    }

    public SwordDto create(SwordDto swordDto) {
        restTemplate.postForLocation("/", swordDto);
        return swordDto;
    }

    public SwordDto readById(Long id) {
        return restTemplate.getForObject(ONE_URI, SwordDto.class, id);
    }

    public List<SwordDto> readAll() {
        SwordDto[] response = restTemplate.getForObject("/", SwordDto[].class);
        if (response != null) {
            return Arrays.asList(response);
        }
        return null;
    }

    public void update(SwordDto swordDto, Long id) {
        restTemplate.put("/" + id, swordDto);
    }


    public void delete(Long id) {
        restTemplate.delete("/" + id);
    }
}
