#include <gtest/gtest.h>

#include <blackhole/attribute.hpp>
#include <blackhole/extensions/writer.hpp>
#include <blackhole/handler/blocking.hpp>
#include <blackhole/record.hpp>
#include <src/handler/blocking.hpp>

#include "mocks/formatter.hpp"
#include "mocks/sink.hpp"

namespace blackhole {
inline namespace v1 {
namespace handler {
namespace {

using ::testing::Invoke;
using ::testing::_;

using namespace testing;

TEST(blocking_t, Handle) {
    std::unique_ptr<mock::formatter_t> formatter_(new mock::formatter_t);
    mock::formatter_t& formatter = *formatter_;

    std::unique_ptr<mock::sink_t> sink_(new mock::sink_t);
    mock::sink_t& sink = *sink_;

    std::vector<std::unique_ptr<sink_t>> sinks;
    sinks.emplace_back(std::move(sink_));

    blocking_t handler(std::move(formatter_), std::move(sinks));

    EXPECT_CALL(formatter, format(_, _))
        .Times(1)
        .WillOnce(Invoke([](const record_t& record, writer_t& writer) {
            EXPECT_EQ(42, record.severity());
            EXPECT_EQ("-", record.message().to_string());
            EXPECT_EQ(0, record.attributes().size());

            writer.write("---");
        }));

    EXPECT_CALL(sink, emit(_, _))
        .Times(1);

    const string_view message("-");
    const attribute_pack pack;
    record_t record(42, message, pack);

    handler.handle(record);
}

}  // namespace
}  // namespace handler
}  // namespace v1
}  // namespace blackhole
