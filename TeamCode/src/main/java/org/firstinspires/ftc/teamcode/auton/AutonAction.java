package org.firstinspires.ftc.teamcode.auton;

public class AutonAction {
    public interface ActionRuner {
        void run(AutonAction action, Auton auton);
    }

    public boolean done = false;
    public String name = "";

    int atNode = 0;
    ActionRuner runner;

    public AutonAction(int atNode, ActionRuner runner, String name) {
        this.atNode = atNode;
        this.runner = runner;
        this.name = name;
    }

    public AutonAction(int atNode, ActionRuner runner) {
        this(atNode, runner, "");
    }

    public void run(Auton auton) {
        this.runner.run(this, auton);
    }
}
