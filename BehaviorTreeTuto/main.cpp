#include "behaviortree_cpp/bt_factory.h"

using namespace BT;

// clang-format off
static const char* xml_text = R"(
 <root main_tree_to_execute="MainTree"  BTCPP_format="4" >
    <BehaviorTree ID="MySubTree">
        <Sequence name="test_sequence">
            <SaySomething   message="BehaviorTree.CPP works!!" />
            <Action ID="SaySomething"  name="SayGreat" message="BehaviorTree.CPP Rocks!!"/>
        </Sequence>
    </BehaviorTree>
     <BehaviorTree ID="MainTree">
        <Sequence name="root">
            <AlwaysSuccess/>
            <SubTree ID="MySubTree"/>
            <ThinkWhatToSay text="{the_answer}"/>
            <SaySomething   message="{the_answer}" />
        </Sequence>
     </BehaviorTree>
 </root>
 )";
// clang-format on

class SaySomething : public BT::SyncActionNode
{
  public:
  SaySomething(const std::string& name, const BT::NodeConfig& config) :
        BT::SyncActionNode(name, config)
  {}

  BT::NodeStatus tick() override
  {
    std::string msg;
    getInput("message", msg);
    std::cout << msg << std::endl;
    return BT::NodeStatus::SUCCESS;
  }

  static BT::PortsList providedPorts()
  {
    return {BT::InputPort<std::string>("message")};
  }
};

class ThinkWhatToSay : public BT::SyncActionNode
{
  public:
  ThinkWhatToSay(const std::string& name, const BT::NodeConfig& config) :
        BT::SyncActionNode(name, config)
  {}

  BT::NodeStatus tick() override
  {
    setOutput("text", "The answer is 42");
    return BT::NodeStatus::SUCCESS;
  }

  static BT::PortsList providedPorts()
  {
    return {BT::OutputPort<std::string>("text")};
  }
};

int main()
{
  BehaviorTreeFactory factory;
  factory.registerNodeType<SaySomething>("SaySomething");
  factory.registerNodeType<ThinkWhatToSay>("ThinkWhatToSay");

  auto tree = factory.createTreeFromText(xml_text);
  printTreeRecursively(tree.rootNode());

  tree.tickWhileRunning();
  return 0;
}
