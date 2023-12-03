#include "engine.cpp"

int main(int argc, char** argv) {

    ConverterJSON conv;
    std::map<std::string, std::vector<Entry>> freqDictionary;
    std::vector<std::string> texts;
    std::vector<std::string> requests;
    InvertedIndex inv;
    inv.UpdateDocumentBase(conv.GetTextDocuments());
    try {
        SearchServer searchSer(inv);
        searchSer.search(searchSer.requestsInput());
        texts = conv.GetTextDocuments();
        requests = conv.GetRequests();
        conv.putAnswers({{{2,5.34},{8,12.7}},{{1,7.67},{2,34.67},{3,6.4}}});
    } catch (OpeningError ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    } catch (JsonFileContainingError ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
